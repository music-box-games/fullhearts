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
* @file   graphics_debug.hpp
* @author Ryan Hanson
* @date   31 Aug 2020
* @par    email: iovita\@musicboxgames.net
* @brief  Code to help debug graphics.
*
*/
/******************************************************************************/

#ifndef _WE_GRAPHICS_DEBUG_HPP_
#define _WE_GRAPHICS_DEBUG_HPP_

#include <string>
#include <vector>
#include <functional>

#include "line2d.hpp"

namespace waifuengine
{
  namespace graphics
  {
    namespace graphics_debug
    {
      namespace gl_function_detailed_errors
      {
        class detailed_error_funcs
        {
        public:
          using data_func_type = std::function<std::vector<std::string>()>;
          using detail_func_type = std::function<std::string()>;

          data_func_type pnames;
          data_func_type ptypes;
          detail_func_type edetails;

          detailed_error_funcs(data_func_type pn, data_func_type pt, detail_func_type ed = []() -> std::string { return std::string(); });
          ~detailed_error_funcs() = default;
        };

        std::vector<std::string> param_names(std::string func_name);
        std::vector<std::string> param_types(std::string func_name);
        std::string extra_details(std::string func_name);

        bool has_detailed_error_info(std::string func_name);

      }
      std::optional<graphics::line2d> get_debug_line(std::size_t hash);
      graphics::line2d gen_debug_line(point_2d a, point_2d b);
    }
  }
}

#endif