#ifndef _WE_BACKGROUND_FACTORY_HPP_
#define _WE_BACKGROUND_FACTORY_HPP_

#include <memory>
#include <unordered_map>

#include "gameobject.hpp"
#include "space.hpp"

namespace waifuengine
{
  namespace factory
  {
    class background_factory
    {
    private:
      static std::unordered_map<std::string, object_management::objectptr> objects;
    public:
      // loads object from archive
      static void load(std::string file);
      // adds a gameobject to the given space that contains a sprite associated with the given name
      // image assets are loaded into memory at launch to avoid loading duplicates
      // function will search for a loaded background asset named <name> and use that
      // if the asset cannot be found, a default asset will be used
      static std::shared_ptr<waifuengine::object_management::gameobject> build(
        std::shared_ptr<waifuengine::object_management::space> sp, // space to put object in
        std::string name // background name
      );
    };
  }
}

#endif