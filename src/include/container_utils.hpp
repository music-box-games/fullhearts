#ifndef _WE_CONTAINER_UTILS_HPP_
#define _WE_CONTAINER_UTILS_HPP_

#include <vector>
#include <algorithm>

namespace waifuengine
{
  namespace utils
  {
    // to be used with a map
    template<class Container, class Key = typename Container::key_type, class ValueType = typename Container::value_type>
    auto list_keys(Container const& c) -> std::vector<Key>
    {
      std::vector<typename Container::key_type> list;
      std::for_each(c.begin(), c.end(), [&list](ValueType const& pair)
      {
        list.push_back(pair.first);
      });
      return list;
    }
  }
}

#endif

