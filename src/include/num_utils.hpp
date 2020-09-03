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
* @file   num_utils.hpp
* @author Ryan Hanson
* @date   31 Aug 2020
* @par    email: iovita\@musicboxgames.net
* @brief  Number utilities
*
*/
/******************************************************************************/

#ifndef _WE_NUM_UTILS_HPP_
#define _WE_NUM_UTILS_HPP_

namespace waifuengine
{
  namespace utils
  {
    template<typename T>
    T clamp(T bot, T top, T value)
    {
      if(value < bot) return bot;
      if(value > top) return top;
      else return value;
    }

    /**
      * @brief Compares if two floats are equal, with an acceptable margin of error.
      * @param a The first float to compare.
      * @param b The second float to compare.
      * @return If the two floats are "equal".
    */
    bool lax_float_compare(float a, float b, float error);

    /**
      * @brief Generates a random int between min and max
      * @param min Minumum value
      * @param b Maximum value
      * @return Generated value.
    */
    int generate_random_int_between(int min, int max);

    /**
      * @brief Generates a random float between min and max
      * @param min Minumum value
      * @param b Maximum value
      * @return Generated value.
    */
    float generate_random_float_between(float min, float max);
  }
}

#endif