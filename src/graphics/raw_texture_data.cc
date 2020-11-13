/****************************************************************************
 *   Copyright (C) 2020 by Music Box Games                                  *
 *                                                                          *
 *   This file is part of WaifuEngine                                       *
 *                                                                          *
 *   WaifuEngine is free software: you can redistribute it and/or modify it *
 *   under the terms of the MIT License.                                    *
 *                                                                          *
 *   WaifuEngine is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   MIT License for more details.                                          *
 *                                                                          *
 *   You should have received a copy of the MIT License along with          *
 *   WaifuEngine.  If not, see https://opensource.org/licenses/MIT          *
 ****************************************************************************/

/******************************************************************************/
/**
* @file   raw_texture_data.cc
* @author Author
* @date   30 Aug 2020
* @par    email: iovita\@musicboxgames.net
* @brief  Class that holds onto texture data, sharing it with texture classes to save data
*
*/
/******************************************************************************/

#include "raw_texture_data.hpp"

#include <SOIL2/SOIL2.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "log.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    raw_texture_data::raw_texture_data(imageptr i, std::string const& n, unsigned int id, std::string shader_name) : name(n), unit_id(0)
    {
      log::LOGTRACE(std::string("Constructing raw_texture_data: " + name));
        im = i;
        width = static_cast<int>(im->dimensions()[0]);
        height = static_cast<int>(im->dimensions()[1]);
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        auto s = shaders::get_shader(shader_name);
        if (s.has_value())
        {
          shd = s.value();
        }
        else
        {
          // warning
          we::log::LOGWARNING(std::string("Could not find shader: " + shader_name));
        }

        load(im);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    raw_texture_data::~raw_texture_data()
    {
      log::LOGTRACE(std::string("Destructing raw_texture_data: " + name));
              glDeleteTextures(1, &txtr);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
        glDeleteVertexArrays(1, &vao);
    }

    void raw_texture_data::draw(float * verts, std::size_t vert_count, unsigned int * elements, std::size_t e_count, transform const& tr) const    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBindTexture(GL_TEXTURE_2D, txtr);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vert_count * sizeof(float), verts, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, e_count * sizeof(unsigned int), elements, GL_STATIC_DRAW);

        int position_attribute = glGetAttribLocation(shd->get_id(), "position");
        glEnableVertexAttribArray(position_attribute);
        glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);

        int tex_attribute = glGetAttribLocation(shd->get_id(), "texcoord");
        glEnableVertexAttribArray(tex_attribute);
        glVertexAttribPointer(tex_attribute, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(5 * sizeof(float)));

        int model_attribute = glGetUniformLocation(shd->get_id(), "model");
        if (model_attribute == -1)
        {
          return;
        }
        int view_attribute = glGetUniformLocation(shd->get_id(), "view");
        if(view_attribute == -1)
        {
          return;
        }

        shd->use();
        shd->set_int_1("tex", 0);

        glUniformMatrix4fv(model_attribute, 1, GL_FALSE, glm::value_ptr(*(tr.const_data())));

        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(e_count), GL_UNSIGNED_INT, 0);
    }

    int raw_texture_data::get_height() const
    {
      return height;
    }

    int raw_texture_data::get_width() const
    {
      return width;
    }

    std::string raw_texture_data::get_name() const
    {
      return name;
    }

    void raw_texture_data::load(imageptr img)
    {
        log::LOGTRACE(std::string("raw_texture_data: \"" + name + "\" loading image: \"" + utils::strip_path_to_filename_and_ext(img->name()) + "\""));
        glGenTextures(1, &txtr);
        
        glBindTexture(GL_TEXTURE_2D, txtr);
        glTexImage2D(GL_TEXTURE_2D, unit_id, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->data());
        glGenerateMipmap(GL_TEXTURE_2D);
        shd->set_int_1("tex", unit_id);
    }
  }
}