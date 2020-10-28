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
* @file   func_utils.hpp
* @author Ryan Hanson
* @date   27 Oct 2020
* @par    email: iovita\@musicboxgames.net
* @brief  Function utilities
*
*/
/******************************************************************************/

#ifndef _WE_FUNC_UTILS_HPP_
#define _WE_FUNC_UTILS_HPP_

#include <string>

namespace waifuengine
{
  namespace utils
  {
    std::string function_name_from_addr(long long addr);
  }
}

#endif