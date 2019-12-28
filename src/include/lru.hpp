#ifndef _WE_LRU_HPP_
#define _WE_LRU_HPP_

#include <list>
#include <unordered_map>

namespace waifuengine
{
  namespace core
  {
    template<class Key, class Value = Key>
    class lru
    {
    private:
      using key_type = Key;
      using value_type = Value;

      std::size_t max_size;
      std::list<key_type> keys;
      std::unordered_map<key_type, std::pair<value_type, decltype(keys.begin())>> data;

      void refer(key_type const& k)
      {
        keys.erase(data[k].second);
        keys.push_front(k);
        data[k].second = keys.begin();
      }

      void evict()
      {
        data.erase(keys.back());
        keys.pop_back();
      }

      void resize(std::size_t const& s)
      {
        if(s < max_size && s < keys.size())
        {
          while(s < keys.size())
          {
            data.erase(keys.back());
            keys.pop_back();
          }
        }
      }

    public:
      lru(std::size_t s = 10) : max_size(s) {}

      ~lru() {}

      void push(key_type const& key, value_type value)
      {
        // if cache is full, evict
        if(keys.size() > max_size) evict();
        // check if key is already present
        auto pos = data.find(key);
        // miss
        if(pos == data.end())
        {
          keys.push_front(key);
          data[key] = {value, keys.front()};
        }
        // hit
        else
        {
          refer(key);
        }
      }

      bool get(key_type const& key, value_type& v)
      {
        if(data.count(key))
        {
          refer(key);
          v = data[key].first;
          return true;
        }
        else return false;
      }

      void set_max_size(std::size_t const& s)
      {
        resize(s);
      }
    };
  }
}

#endif // !_WE_LRU_HPP_