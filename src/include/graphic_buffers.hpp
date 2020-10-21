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
* @file   graphic_buffers.hpp
* @author Ryan Hanson
* @date   10 Oct 2020
* @par    email: iovita\@musicboxgames.net
* @brief  Reference counted wrappers around openGL buffers
*
* 
*/
/******************************************************************************/

#ifndef _WE_GRAPHIC_BUFFERS_HPP_
#define _WE_GRAPHIC_BUFFERS_HPP_

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace waifuengine
{
  namespace graphics
  {
    namespace buffers
    {
      class vertex_array_object
      {
      private:
        std::string name_;
        GLuint vao;

      public:
        vertex_array_object(std::string const& n);
        ~vertex_array_object();

        std::string name() const;
        GLuint data() const;
      };

      class vertex_buffer_object
      {
      private:
        std::string name_;
        GLuint vbo;

      public:
        vertex_buffer_object(std::string const& n);
        ~vertex_buffer_object();

        std::string name() const;
        GLuint data() const;
      };

      class element_buffer_object
      {
      private:
        std::string name_;
        GLuint ebo;

      public:
        element_buffer_object(std::string const& n);
        ~element_buffer_object();

        std::string name() const;
        GLuint data() const;
      };
    }
  }
}

#endif