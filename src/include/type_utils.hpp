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
* @file   stub.hpp
* @author Author
* @date   1 Jan 2970
* @par    email: email\@domain
* @brief  A brief description of the file.
*
* A more in depth description of the file's functionality.
*/
/******************************************************************************/

#ifndef _WE_TYPE_UTILS_HPP_
#define _WE_TYPE_UTILS_HPP_

#include <cstdarg>
#include <string>
#include <sstream>

namespace waifuengine
{
  namespace utils
  {
    template<class T>
    T get_va_arg(va_list l)
    {
      return va_arg(l, T);
    }

    void insert_va_arg_into_sstream(std::stringstream & ss, std::string const& type, va_list list);
  }
}

#endif