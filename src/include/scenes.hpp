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

#include <serialization.hpp>
#include <spacemanager.hpp>
#include <component.hpp>
#include <debug.hpp>

#define SCENE_NAME(x) static constexpr std::string_view NAME = #x

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace scenes
  {
    class scene
    {
    protected:
      ::waifuengine::object_management::space_manager manager;

    private:
      friend class waifuengine::core::debug::imgui_listener;
      friend class ::boost::serialization::access;
      template<class Archive>
      void serialize(Archive& ar, unsigned int const version)
      {
        ar & manager;
        ar & name;
      }

    public:
      std::string name;

      virtual void update(float dt);
      virtual void draw() const;

      scene(std::string n = "");
      virtual ~scene();

      we::object_management::space_manager * get_manager();

      virtual bool operator==(scene const& rhs) const;
    };
  }
}

BOOST_CLASS_EXPORT_KEY(waifuengine::scenes::scene);

#endif // !_WE_SCENES_HPP_
