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
      class imgui_listener
      {
      private:
        static const std::size_t HISTOGRAM_LEN = 300;
        std::deque<float> fps_histogram;
      
      public:
        imgui_listener() {}
        ~imgui_listener() {}

        void run()
        {
          ImGui::Begin("Debug");

          ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
          fps_histogram.push_back(ImGui::GetIO().Framerate);
          if (fps_histogram.size() > HISTOGRAM_LEN)
          {
            fps_histogram.pop_front();
          }
          static std::array<float, HISTOGRAM_LEN> values;
          std::copy(fps_histogram.begin(), fps_histogram.end(), values.begin());
          std::stringstream ss;
          ss << "Framerate\n(Last " << HISTOGRAM_LEN << " frames)\nLimit: " << we::core::settings::read_t<std::size_t>("frame_limit");
          ImGui::PlotLines(ss.str().c_str(), values.data(), HISTOGRAM_LEN, 0, NULL, 0, 144, ImVec2(0, 0), 4);

          ImGui::End();
        }
      };

      namespace impl
      {
        bool show_debug_window = false;
        bool debug_ready_to_draw = false;

        imgui_listener listener;
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
          impl::listener.run();
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