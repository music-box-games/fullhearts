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

#include <cmath>
#include <random>
#include <ctime>

#include "num_utils.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace utils
  {
    bool lax_float_compare(float a, float b, float error)
    {
      float diff = a - b;
      // TODO: this might introduce more error
      if(diff < 0)
      {
        diff *= -1;
      }
      return diff < error;
    }

    int generate_random_int_between(int min, int max)
    {
      std::mt19937 rng(static_cast<unsigned int>(std::time(NULL)));
      std::uniform_int_distribution<int> gen(min, max); // uniform, unbiased
      return gen(rng);
    }

    float generate_random_float_between(float min, float max)
    {
      return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
    }
  }
}