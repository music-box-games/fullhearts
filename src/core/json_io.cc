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
* @file   json_io.cc
* @author Ryan Hanson
* @date   3 Sept 2020
* @par    email: iovita\@musicboxgames.net
* @brief  JSON i/o functionality.
*
* Basically just a wrapper for https://github.com/nlohmann/json with some
* useful goodies here and there
*/
/******************************************************************************/

#include "json_io.hpp"


namespace we = ::waifuengine;
namespace njson = ::nlohmann;

namespace waifuengine
{
  namespace core
  {
    namespace io
    {
      namespace json
      {
        std::any any_extract(njson::json const& j, std::string const& key)
        {
          return std::any(j[key]);
        }
      }
    } // namespace io
  }   // namespace core
} // namespace waifuengine