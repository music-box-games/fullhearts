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
* @file   texture.hpp
* @author Ryan Hanson
* @date   30 Aug 2020
* @par    email: iovita\@musicboxgames.net
* @brief  Texture class
*
*/
/******************************************************************************/

#ifndef _WE_TEXTURE_HPP_
#define _WE_TEXTURE_HPP_

#include <vector>
#include <string>
#include <memory>
#include <optional>
#include <array>
#include <set>
#include <glm/glm.hpp>

#include "filesystem.hpp"
#include "image.hpp"
#include "shader.hpp"
#include "gameobject.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "debug.hpp"
#include "raw_texture_data.hpp"

namespace waifuengine
{
  namespace graphics
  {
    namespace textures
    {
      class texture
      {
      public:
        static constexpr int VERT_COUNT = 28;
        static constexpr int ELEMENT_COUNT = 6;

        using vert_array = std::array<float, VERT_COUNT>;
        using element_array = std::array<unsigned int, ELEMENT_COUNT>;

      private:
        friend class waifuengine::core::debug::imgui_listener;


        vert_array vertices; /**< array of vertices */
        element_array elements; /**< array of elements */

        std::string name; /**< texture name */
        waifuengine::graphics::transform last_trans; /**< copy of last transform passed to update() */
        std::shared_ptr<raw_texture_data> tdata; /**< texture */

      public:
        texture(raw_txtr_ptr d);
        ~texture();

        vert_array get_vertices() const;

        void draw() const;
        void update(transform const& t = transform());
        void set_transform();   

        glm::vec2 texture_dimensions() const;  

      };

      using textureptr = std::shared_ptr<texture>;

      std::vector<std::string> list_loaded_textures();
      std::vector<std::string> list_loaded_images();
      std::set<std::string> list_image_files();
      std::unordered_map<std::string, fs::path> list_image_paths();

      std::shared_ptr<raw_texture_data> get_raw_texture(std::string const& name);
      texture get_texture(std::string const& name);
      std::optional<std::shared_ptr<image>> get_image(std::string const& name);
      std::unordered_map<std::string, std::shared_ptr<raw_texture_data>> get_texturemap();

      void load_textures();
      std::shared_ptr<raw_texture_data> load_texture(std::string const& image_name, std::string const& shader_name);
      void load_images();
      imageptr load_image(std::string const& name);

      void release_textures();
      void release_images();


      namespace test
      {
        class texture_test_object : public we::object_management::gameobject
        {
        protected:
          texture tex;

        public:
          texture_test_object(std::string const& name, std::string const& texture_name, std::string const& shader_name);
          virtual ~texture_test_object();

          virtual void update(float);
          virtual void draw() const;
        };
      }
    }
  }
}

#endif