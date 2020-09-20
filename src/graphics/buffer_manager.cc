
#include <optional> // std::optional
#include <unordered_map> // std::unordered_map

#include "buffer_manager.hpp"
#include "utils.hpp"
#include "graphics.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    namespace buffer_manager
    {
      namespace impl
      {
        using buffermap_key_type = buffer_request_key;
        using buffermap_value_type = raw_buffer_reference_counter;
        using buffer_map = std::unordered_map<buffermap_key_type, buffermap_value_type>;

        buffer_map active_vaos;
        buffer_map active_vbos;
        buffer_map active_ebos;

        buffer_map idle_vaos;
        buffer_map idle_vbos;
        buffer_map idle_ebos;

        static buffer_raw_type gen_buffer(buffer_types t)
        {
          // TODO: error checking
          buffer_raw_type b;
          auto vbo_ebo_generator = []() -> buffer_raw_type 
          {
            buffer_raw_type b;
            glGenBuffers(1, &b);
            return b;
          };

          switch(t)
          {
            case buffer_types::VAO:
              glGenVertexArrays(1, &b);
              return b;
            case buffer_types::VBO:
              return vbo_ebo_generator();
            case buffer_types::EBO:
              return vbo_ebo_generator();
            default:
              return buffer_raw_type();
          }
        }

        static void release_buffer(buffer_types t, buffer_raw_type b)
        {
          auto vbo_ebo_releaser = [](buffer_raw_type bb) -> void
          {
            glDeleteBuffers(1, &bb);
          };

          switch (t)
          {
          case buffer_types::VAO:
            glDeleteVertexArrays(1, &b);
            break;

          case buffer_types::VBO:
            vbo_ebo_releaser(b);
            break;
          
          case buffer_types::EBO:
            vbo_ebo_releaser(b);
            break;
          
          default:
            break;
          }
        }


        std::optional<buffer_map::iterator> check_buffers(buffermap_key_type const& key)
        {
          // only checks the idle buffers for now
          if(idle_ebos.count(key))
          {
            return idle_ebos.find(key);
          }
          if(idle_vbos.count(key))
          {
            return idle_vbos.find(key);
          }
          if(idle_vaos.count(key))
          {
            return idle_vaos.find(key);
          }
          return {};
        }

        std::optional<buffer_map::iterator> check_buffers(buffer_types bt, buffermap_key_type const& key)
        {
          switch(bt)
          {
            case buffer_types::VAO:
              if(idle_vaos.count(key))
              {
                return idle_vaos.find(key);
              }
              else return {};
            case buffer_types::VBO:
              if(idle_vbos.count(key))
              {
                return idle_vbos.find(key);
              }
              else return {};
            case buffer_types::EBO:
              if(idle_ebos.count(key))
              {
                return idle_ebos.find(key);
              }
              else return {};
            default:
              return {};
          }
        }

        buffermap_key_type add_reference_counter(buffer_types bt)
        {
          auto b = decltype(idle_vaos.emplace(buffermap_value_type(bt)))();
          auto value = buffermap_value_type(bt);

          switch(bt)
          {
            case buffer_types::VAO:
              b = idle_vaos.emplace(value.raw().raw(), value);
              if(b.second)
              {
                return b.first->second.raw().raw();
              }
              else return buffermap_key_type();
            case buffer_types::VBO:
              b = idle_vbos.emplace(value.raw().raw(), value);
              if(b.second)
              {
                return b.first->second.raw().raw();
              }
              else return buffermap_key_type();
            case buffer_types::EBO:
              b = idle_ebos.emplace(value.raw().raw(), value);
              if(b.second)
              {
                return b.first->second.raw().raw();
              }
              else return buffermap_key_type();
            default:
              return buffermap_key_type();
          }
        }
       
        template<class Key>
        static bool check_buffermap_key(Key k) { return false; }
        template<>
        static bool check_buffermap_key(std::string const& k)
        {
          return !k.empty();
        }
        template<>
        static bool check_buffermap_key(unsigned int const& k)
        {
          return k != 0;
        } 
      }

      raw_buffer_wrapper::raw_buffer_wrapper(buffer_types t, buffer_raw_type d) : released(false), type(t), data(d)
      {

      }

      raw_buffer_wrapper::raw_buffer_wrapper(buffer_types t) : released(false), type(t), data(impl::gen_buffer(t))
      {

      }

      raw_buffer_wrapper::~raw_buffer_wrapper()
      {
        if(!released)
        {
          release();
        }
      }

      void raw_buffer_wrapper::release()
      {
        if(!released)
        {
          impl::release_buffer(type, data);
          released = true;
        }
      }

      bool raw_buffer_wrapper::is_released()
      {
        return released;
      }

      buffer_raw_type raw_buffer_wrapper::raw()
      {
        return data;
      }


      buffer_handle::buffer_handle(buffer_wrapper_type const& b) : data(b) {}

      buffer_handle::~buffer_handle()
      {
        // TODO: decrease reference count with counter
      }

      buffer_wrapper_type buffer_handle::get_wrapper()
      {
        return data;
      }

      raw_buffer_reference_counter::raw_buffer_reference_counter(buffer_types bt) : references(1), type(bt), data(raw_buffer_wrapper(bt)), released(false)
      {

      }

      raw_buffer_reference_counter::~raw_buffer_reference_counter()
      {
        if(!released)
        {
          release();
        }
      }

      void raw_buffer_reference_counter::add_reference()
      {
        if(!released)
        {

          ++references;
        }
      }

      void raw_buffer_reference_counter::remove_reference()
      {
        if(!released)
        {

        --references;
        handle_ref_count();
        }
      }

      void raw_buffer_reference_counter::handle_ref_count()
      {
        if(references == 0)
        {
          release();
        }
      }

      void raw_buffer_reference_counter::release()
      {
        data.release();
      }

      buffer_handle_type raw_buffer_reference_counter::spawn_handle()
      {
        return buffer_handle_type(data);
      }


      buffer_handle_type request_buffer(buffer_types bt, buffer_request_key key)
      {
        // if key is invalid (or just 0 if unsigned int), generate new buffer
        if(!impl::check_buffermap_key(key))
        {
          // create a new reference counter, which will create the buffer
          key = impl::add_reference_counter(bt);
          return buffer_handle_type(raw_buffer_wrapper(bt, key));
        }
        // check for already stored buffers with the same key
        auto opt = impl::check_buffers(bt, key);
        if(opt.has_value())
        {
          auto val = opt.value();
          return val->second.spawn_handle();
        }       
        // cannot create a buffer with a given key atm
      }
    }
  }
}