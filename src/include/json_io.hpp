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
* @file   json_io.hpp
* @author Ryan Hanson
* @date   3 Sept 2020
* @par    email: iovita\@musicboxgames.net
* @brief  JSON i/o functionality.
*
* Basically just a wrapper for https://github.com/nlohmann/json with some
* useful goodies here and there
*/
/******************************************************************************/

#ifndef _WE_JSON_IO_HPP_
#define _WE_JSON_IO_HPP_

#include <any>

#include <nlohmann/json.hpp>

namespace waifuengine
{
  namespace core
  {
    namespace io
    {
      namespace json
      {
        /**
          * @brief Extracts the value at key in a .JSON file
          * @param j The .JSON file to extract the value from
          * @param key The key the value is stored at
          * @return The value stored at key
        */
        std::any any_extract(::nlohmann::json const& file, std::string const& key);

        template<class T>
        T extract(::nlohmann::json const& file, std::string const& key)
        {
          return static_cast<T>(file[key]);
        }
      }
    }
  }
}

#endif