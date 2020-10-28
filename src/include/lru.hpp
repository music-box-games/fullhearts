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
* @file   lru.hpp
* @author Ryan Hanson
* @date   23 Oct 2020
* @par    email: iovita\@musicboxgames.net
* @brief  Implementation of an LRU cache
*
*/
/******************************************************************************/

#ifndef _WE_LRU_HHP_
#define _WE_LRU_HHP_

#include <cstddef> // std::size_t
#include <unordered_map> // std::unordered_map
#include <functional> // std::hash
#include <optional> // std::optional
#include <list> // std::list
#include <algorithm> // std::for_each
#include <thread> // std::scoped_lock
#include <mutex> // std::mutex

namespace waifuengine
{
namespace cache
{
  using hash_value_type = std::size_t;
  template<class data_type, class key_type = hash_value_type, class list_iter = typename std::list<std::pair<key_type, data_type>>::iterator>
  class LRU
  {
  public:
    using map_type = std::unordered_map<key_type, list_iter>;
    using list_type = std::list<std::pair<key_type, data_type>>;

  private:
    std::size_t cache_limit;
    map_type cache_map;
    list_type cache_list;
    std::mutex mt;

    void refer(key_type h)
    {
      if (!cache_map.count(h))
      {
        return;
      }
      auto map_it = cache_map.find(h);
      auto list_pair = *(map_it->second);
      cache_list.erase(map_it->second);
      cache_list.push_front(list_pair);
      cache_map[h] = cache_list.begin();
    }

  public:
    LRU(std::size_t cache_size) : cache_limit(cache_size) {}
    ~LRU() {}

    void put(key_type h, data_type d)
    {
      // if the value is already present in the cache, move it to the front
      auto it = cache_map.find(h);
      if (it != cache_map.end())
      {
        cache_list.erase(it->second);
        cache_map.erase(it);
      }
      cache_list.emplace_front(h, d);
      cache_map.emplace(h, cache_list.begin());
    }

    std::optional<data_type> get(key_type h)
    {
      if (contains(h))
      {
        refer(h);
        return (*cache_map[h]).second;
      }
      else
      {
        return {};
      }
    }

    bool contains(key_type h)
    {
      return cache_map.count(h);
    }

    list_type const& data() const
    {
      return cache_list;
    }
  };
}

template<class DataType>
std::ostream& operator<<(std::ostream& os, waifuengine::cache::LRU<DataType> const& c)
{
  auto const& l = c.data();
  os << '{';
  std::for_each(l.begin(), l.end(), [&os](DataType const& d) -> void {
    os << d << ',';
    });
  os << '}';
  return os;
}
}

#endif