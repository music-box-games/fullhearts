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
* @file   buffer_manager.cc
* @author Ryan hanson
* @date   11 Oct 2020
* @par    email: iovita\@musicboxgames.net
* @brief  Manages OpenGL buffers to allow for triviable copying of objects
*         with buffers as members.
*
* 
*/
/******************************************************************************/

#include <iostream>
#include <unordered_map>

#include "graphic_buffer_manager.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    namespace buffer_manager
    {
      namespace impl
      {
        template<class buffer_type>
        using underlying_buffer_map_type = std::unordered_map<GLuint, buffer_type>;

        static underlying_buffer_map_type<vao_handle::buffer_t> underlying_vaos;
        static underlying_buffer_map_type<vbo_handle::buffer_t> underlying_vbos;
        static underlying_buffer_map_type<ebo_handle::buffer_t> underlying_ebos;
      }

      using buffer_map_type = std::unordered_map<std::string, GLuint>;
      static buffer_map_type vaos;
      static buffer_map_type vbos;
      static buffer_map_type ebos;

      template<class buffer_type, class buffer_t = buffer_type::buffer_t>
      static std::optional<buffer_type> new_handle_t(buffer_map_type& bmap, impl::underlying_buffer_map_type<buffer_t>& underlying_bmap, std::string const& name)
      {
        if(bmap.count(name))
        {
          // errors if a buffer already exists with the name
          return {};
        }
        else
        {
          // construct at index '0', because that is only for errors anyways
          auto p = underlying_bmap.emplace((GLuint)0, buffer_type::buffer_t(name));
          if(!p.second)
          {
            return {}; // p.second is false if it failed to emplace
            // TODO: error handle
          }
          GLuint id = p.first->second.data();
          auto node = underlying_bmap.extract(0); // extra the node for the newly made entry and change the key to the GLuint id
          node.key() = id;
          underlying_bmap.insert(std::move(node));
          bmap[name] = id;
          return buffer_type(underlying_bmap.at(id));
        }
      }

      template<class buffer_type, class buffer_t = buffer_type::buffer_t>
      static std::optional<buffer_type> get_handle_t(buffer_map_type& bmap, impl::underlying_buffer_map_type<buffer_t>& underlying_bmap, std::string const& name)
      {
        if(bmap.count(name))
        {
          return buffer_type(underlying_bmap.at(bmap.at(name)));
        }
        else
        {
          // fail if doesn't exist
          return {};
        }
      }

      vao_handle::vao_handle(graphics::buffers::vertex_array_object & d) : data(d) {}
      vao_handle::~vao_handle() {}
      std::optional<vao_handle> vao_handle::new_handle(std::string const& name)
      {
        return new_handle_t<vao_handle, vao_handle::buffer_t>(vaos, impl::underlying_vaos, name);
      }

      std::optional<vao_handle> vao_handle::get_handle(std::string const& name)
      {
        return get_handle_t<vao_handle, vao_handle::buffer_t>(vaos, impl::underlying_vaos, name);
      }

      vbo_handle::vbo_handle(graphics::buffers::vertex_buffer_object & d) : data(d) {}
      vbo_handle::~vbo_handle() {}
      std::optional<vbo_handle> vbo_handle::new_handle(std::string const& name)
      {
        return new_handle_t<vbo_handle, vbo_handle::buffer_t>(vbos, impl::underlying_vbos, name);
      }
      std::optional<vbo_handle> vbo_handle::get_handle(std::string const& name)
      {
        return get_handle_t<vbo_handle, vbo_handle::buffer_t>(vbos, impl::underlying_vbos, name);
      }

      ebo_handle::ebo_handle(graphics::buffers::element_buffer_object & d) : data(d) {}
      ebo_handle::~ebo_handle() {}
      std::optional<ebo_handle> ebo_handle::new_handle(std::string const& name)
      {
        return new_handle_t<ebo_handle, ebo_handle::buffer_t>(ebos, impl::underlying_ebos, name);
      }

      std::optional<ebo_handle> ebo_handle::get_handle(std::string const& name)
      {
        return get_handle_t<ebo_handle, ebo_handle::buffer_t>(ebos, impl::underlying_ebos, name);
      }
    }
  }
}