/******************************************************************************/
/*!
\file   scenes.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Scene class. A scene contains a space manager to manage spaces and objects.

*/
/******************************************************************************/

#ifndef _WE_SCENES_HPP_
#define _WE_SCENES_HPP_

#include <unordered_map>

#include <spacemanager.hpp>

#define SCENE_NAME(x) static constexpr std::string_view NAME = #x

// TODO: Currently only one instance of each scene allowed

namespace waifuengine
{
  namespace scenes
  {
    class scene
    {
    protected:
      ::waifuengine::object_management::space_manager manager;

    public:
      std::string NAME;

      void update(float dt);
      void draw() const;

      scene(std::string n);
      virtual ~scene();
    };
  }
}

#endif // !_WE_SCENES_HPP_
