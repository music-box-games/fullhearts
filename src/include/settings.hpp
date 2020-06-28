/******************************************************************************/
/*!
\file   settings.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Engine and game settings.

*/
/******************************************************************************/

#ifndef _WE_SETTINGS_HPP_
#define _WE_SETTINGS_HPP_

#include <any>

#include <serialization.hpp>
#include "debug.hpp"

#include "events.hpp"

namespace waifuengine
{
  namespace core
  {
    class settings
    {
    public:
      class settings_change_event : public waifuengine::events::event
      {
      public:
        EVENT_NAME(settings_change_event);

        settings_change_event();
        settings_change_event(std::string n, std::any o_value, std::any n_value);

        std::string name;
        std::any old_value;
        std::any new_value;

        void reset();
      };

      class setting_value
      {
      public:
        std::string name;
        std::any value;

        setting_value(std::string n, std::any v);
        ~setting_value() = default;

        template<typename ValueType>
        ValueType read_t() const
        {
          return std::any_cast<ValueType>(value);
        }

        template<typename ValueType>
        void write_t(ValueType const& v)
        {
          value.reset();
          value = std::any(v);
        }
      };
    private:
      friend class waifuengine::core::debug::imgui_listener;
      static std::unordered_map<std::string, setting_value> values;

      friend class boost::serialization::access;
      template <class Archive>
      void serialize(Archive &ar, unsigned int const v)
      {
        
      }

      static void send_change_event(std::string n, std::any o_value, std::any n_value);

      static void * get_raw_pointer_to(std::string name);

    public:
      settings() = default;
      ~settings() = default;

      static void save(settings const &s);
      static void load();

      template<typename ValueType>
      static ValueType read_t(std::string name)
      {
        return values.at(name).read_t<ValueType>();
      }

      template<typename ValueType>
      static void write_t(std::string name, ValueType const& v)
      {
        ValueType old = values.at(name).read_t<ValueType>();
        values.at(name).write_t<ValueType>(v);
        send_change_event(name, old, v);
      }
    };
  }     // namespace core
} // namespace waifuengine


#endif // !_WE_SETTINGS_HPP_