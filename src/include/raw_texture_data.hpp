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
* @file   raw_texture_data.hpp
* @author Ryan Hanson
* @date   30 Aug 2020
* @par    email: iovita\@musicboxgames.net
* @brief  Class that holds onto texture data, sharing it with texture classes to save data
*
*/
/******************************************************************************/

#ifndef _WE_RAW_TEXTURE_DATA_HPP_
#define _WE_RAW_TEXTURE_DATA_HPP_

#include <memory>

#include "image.hpp"
#include "graphics.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "debug.hpp"
#include "transform.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class raw_texture_data
    {
    private:
        friend class core::debug::imgui_listener;

        unsigned int unit_id; /**< texture unit ID */
        unsigned int txtr; /**< texture data */
        std::shared_ptr<shaders::shader> shd; /**< shader */
        unsigned int vao; /**< vertex array object */
        unsigned int vbo; /**< vertex buffer object */
        unsigned int ebo; /**< element buffer object */

        int width; /**< texture's width in pixels */
        int height; /**< texture's height in pixels */
        std::shared_ptr<image> im; /**< image file for texture */

        std::string name;

    public:
      /**
        * @brief Constructor
      */
      raw_texture_data(imageptr image, std::string const& name, unsigned int id, std::string shader_name);

      /**
        * @brief Destructor
      */
      ~raw_texture_data();

      void draw(float * verts, std::size_t vert_count, unsigned int * elements, std::size_t e_count, transform const& tr) const;

      int get_width() const;
      int get_height() const;
      std::string get_name() const;

      void load(imageptr img);
    };

    using raw_txtr_ptr = std::shared_ptr<raw_texture_data>;
  } // namespace graphics
  
}

#endif
