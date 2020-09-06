/******************************************************************************/
/*!
\file   component.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
    Component base classes. Components are where all the game magic happens.

*/
/******************************************************************************/

#ifndef _W_COMPONENT_HPP_
#define _W_COMPONENT_HPP_

#include <string>
#include <string_view>
#include <typeinfo>
#include <typeindex>

#include <serialization.hpp>

#include "component_order.hpp"

#define COMPONENT_NAME(x) static constexpr const char *NAME = #x // macro for using the class as the component's name
#define COMPONENT_TYPE(x) static constexpr ::waifuengine::components::component_types TYPE = ::waifuengine::components::component_types::x
#define COMPONENT_ORDER(x) static constexpr int ORDER = ::waifuengine::components::order::component_order::x

#define COMPONENT_REGISTER(x) COMPONENT_NAME(x);COMPONENT_TYPE(x);COMPONENT_ORDER(x);

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace object_management
  {
    class gameobject;
  }
} // namespace waifuengine

namespace waifuengine
{
  namespace components
  {
    class dummy;

    enum class component_types : int
    {
      debug_draw,
      physics,
      physics2,
      collider,
      box_collider,
      button_collider,
      mouse_collider,
      transform,
      shader,
      texture,
      sprite,
      textsprite,
      script_object,

      // special ones
      basic_shape,
      basic_triangle,
      dummy,
    };

    class component_sorter
    {
    public:
      bool operator()(std::string a, std::string b) const;

      static void register_component(std::string a, int o);
    };

    namespace _impl
    {
      class _base_component
      {
      public:
        std::string name;
        component_types type;
        int order;
        we::object_management::gameobject *parent;
        bool disabled = false;
        bool debugging = false; // TODO: make this in #ifdef DEBUG only

        _base_component(std::string n, component_types t, int o) : name(n), type(t), order(o), parent(nullptr) {}
        virtual ~_base_component() {}

        virtual void update(float dt) = 0;
        virtual void draw() const = 0;
        virtual void draw_debug() = 0;
        virtual void disable(bool set = true) { disabled = set; }
        virtual bool is_disabled() const { return disabled; }
        virtual void debug(bool set = true) { debugging = set; }
        virtual bool is_debugging() const { return debugging; }

        operator std::string() { return name; }
        bool operator<(_base_component const &rhs) { return type < rhs.type; }

        //virtual void operator=(_base_component const &rhs) = 0;
        virtual bool operator==(_base_component const &rhs) = 0;

      private:
        friend class boost::serialization::access;
        template <class Archive>
        void serialize(Archive &ar, unsigned int const)
        {
          ar &name;
          ar &type;
        }
      };
      BOOST_SERIALIZATION_ASSUME_ABSTRACT(_base_component)
    } // namespace _impl

    template <typename _Derive>
    class component : public _impl::_base_component
    {
    public:
      component() : _impl::_base_component(_Derive::NAME, _Derive::TYPE, _Derive::ORDER) 
      {
        // register component with sorting
        component_sorter::register_component(name, order);
      }
      
      virtual ~component() {}

      virtual void update(float dt) {}
      virtual void draw() const {}
      virtual void draw_debug() {}

      virtual void disable(bool set = true)
      {
        disabled = set;
      }

      virtual void operator=(_base_component const &rhs)
      {
        name = rhs.name;
        type = rhs.type;
      }
      virtual bool operator==(_base_component const &rhs)
      {
        return (name == rhs.name) && (type == rhs.type);
      }

    private:
      friend class boost::serialization::access;
      template <class Archive>
      void serialize(Archive &ar, unsigned int const version)
      {
        ar &boost::serialization::base_object<_impl::_base_component>(*this);
      }
    };

    using compptr = std::shared_ptr<_impl::_base_component>;
  } // namespace components
} // namespace waifuengine
// forward declarations for components
namespace waifuengine
{
  namespace physics
  {
    class collider;
  }
  namespace core
  {
    namespace scripting
    {
      class script_object;
    }
  } // namespace core
} // namespace waifuengine

BOOST_CLASS_EXPORT_KEY(we::components::component<we::core::scripting::script_object>);

#endif // !_W_COMPONENT_HPP_