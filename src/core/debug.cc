#include <deque>
#include <array>
#include <string>
#include <cstring>

#include <SFML/Graphics.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include "debug.hpp"
#include "window.hpp"
#include "scenemanager.hpp"
#include "spacemanager.hpp"
#include "space.hpp"
#include "gameobject.hpp"
#include "component.hpp"
#include "scenes.hpp"
#include "scenelist.hpp"
#include "gameobject.hpp"
#include "scripting.hpp"
#include "texture.hpp"
#include "events.hpp"
#include "event_manager.hpp"
#include "sprite.hpp"
#include "graphics.hpp"

// TODO: forward declare tree functions in imgui_listener or something

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace core
  {
    namespace debug
    {
      namespace impl
      {
        bool show_debug_window = false;
        bool debug_ready_to_draw = false;
      }
      void init_imgui()
      {
        ImGui::SFML::Init(*graphics::get_window_manager().lock()->get_main_window().lock()->data().lock());
      }

      void shutdown_imgui()
      {
        ImGui::SFML::Shutdown();
      }

      void toggle_imgui_window()
      {
        impl::show_debug_window = !impl::show_debug_window;
      }

      void render_imgui()
      {
        static sf::Clock dclk;
          ImGui::SFML::Update(*graphics::get_window_manager().lock()->get_main_window().lock()->data().lock(), dclk.restart());
        
          ImGui::Begin("Debug");
          
          ImGui::End();
          impl::debug_ready_to_draw = true;
        // do stuff
      }

      void present_imgui()
      {
          ImGui::SFML::Render(*graphics::get_window_manager().lock()->get_main_window().lock()->data().lock());
          impl::debug_ready_to_draw = false;
      }

    } // namespace debug
  }   // namespace core
} // namespace waifuengine