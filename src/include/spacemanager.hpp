/******************************************************************************/
/*!
\file   spacemanager.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
    The space manager class contains and manages spaces.

*/
/******************************************************************************/

#ifndef _W_SPACE_MANAGER_HPP_
#define _W_SPACE_MANAGER_HPP_

#include <memory>
#include <string>
#include <map>

#include <space.hpp>
#include <component.hpp>
#include <debug.hpp>

namespace waifuengine
{
  namespace object_management
  {
    struct default_spaces
    {
      using ptrt = std::shared_ptr<space>;

      ptrt bg;
      ptrt ch;
      ptrt fx;
      ptrt ui;
      ptrt tr;
    };

    class space_manager
    {
    private:
      std::map<std::string, space_order> const defaults =
          {
              {"Background Space", space_order::BACKGROUND},
              {"Character Space", space_order::CHARACTER},
              {"FX Space", space_order::FX},
              {"UI Space", space_order::UI},
              {"Transition Space", space_order::TRANSITION},
      };
          class space_sort
      {
      public:
        bool operator()(std::string const& a, std::string const& b) const
        {
          std::map<std::string, int> order =
          {
            {"Background Space", 0},
            {"Character Space", 1},
            {"Unordered Space", 2},
            {"FX Space", 3},
            {"UI Space", 4},
            {"Transition Space", 5},
          };

          return order[a] < order[b];
        }
      };

      std::map<std::string, std::shared_ptr<space>, space_sort> spaces_;

      friend class waifuengine::core::debug::imgui_listener;


    public:
      space_manager();
      ~space_manager();

      std::shared_ptr<space> add_space(std::string n, space_order o = space_order::UNORDERED);
      void remove_space(std::string n);
      std::shared_ptr<space> get_space(std::string n);
      bool has_space(std::string n);

      void update(float dt);
      void draw() const;

      std::size_t spaces() const;
      std::size_t objects() const;
      std::size_t components() const;

      void clear();
      void remove_object(std::string n);

      default_spaces build_default_spaces();

      bool operator==(space_manager const &rhs) const;
    };
  } // namespace object_management
} // namespace waifuengine


#endif // !_W_SPACE_MANAGER_HPP_