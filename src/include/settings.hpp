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

#include <serialization.hpp>

namespace waifuengine
{
  namespace core
  {
    namespace settings
    {
      void load();
      void save();

      extern bool pedantic_debug;
      extern bool mt_messaging;
      extern bool fullscreen;

      extern int window_width;
      extern int window_height;
      
      namespace impl
      {
        // TODO: this is dumb. make it not dumb.
        class settings_state
        {
        private:
          // bool settings
          bool pedantic_debug;
          bool mt_messaging;
          bool fullscreen;

          // int settings
          int window_width;
          int window_height;

          friend class ::boost::serialization::access;
          template<class Archive>
          void serialize(Archive& ar, unsigned int const version)
          {
            ar & pedantic_debug;
            ar & mt_messaging;
            ar & fullscreen;
            ar & window_width;
            ar & window_height;
          }
        public:
          settings_state(bool load_current = true);
          ~settings_state();

          void load_current_settings();
          void apply() const;

          bool operator==(settings_state const& rhs) const;
        };
      }
    }
  }
}

BOOST_CLASS_EXPORT_KEY(waifuengine::core::settings::impl::settings_state);

#endif // !_WE_SETTINGS_HPP_