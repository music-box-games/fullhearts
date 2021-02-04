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
#include "window_manager.hpp"
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
        std::weak_ptr<sf::RenderWindow> main_window;

      public:
        imgui_listener() {}
        ~imgui_listener() {}

        void run()
        {
          main_window = graphics::get_window_manager().lock()->get_main_window().lock()->data();
          if(!ImGui::Begin("Debug"))
          {
            ImGui::End();
          }
          else
          {

          fps_graph();
          mouse_pos();
          main_window_info();
          current_scene();
          ImGui::End();
          }
        }

        void fps_graph()
        {

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

        }

        void mouse_pos()
        {
          auto w = main_window.lock();
          auto p = sf::Mouse::getPosition(*w);
          int mx = p.x;
          int my = p.y;
          ImGui::Text("Mouse Pos: %d, %d", mx, my);
        }

        void main_window_info()
        {
          unsigned ww, wh;
          sf::Vector2u window_dimensions = main_window.lock()->getSize();
          ww = window_dimensions.x;
          wh = window_dimensions.y;
          ImGui::Text("Main Window:\nWidth:%d\nHeight:%d", ww, wh);
        }

        void component_tree(std::pair<const std::string, waifuengine::components::compptr> & c)
        {
          // TODO: use a switch statement with c.second->type
          if(c.first == std::string("sprite"))
          {
            graphics::sprite * spr = dynamic_cast<graphics::sprite *>(c.second.get());
            if(!spr) return;
            spr->sp;
            ImGui::Text("Position: %d, %d", spr->sp.getPosition().x, spr->sp.getPosition().y);
            if(ImGui::TreeNode("Texture"))
            {
              auto texsize = spr->tex.data().getSize();
              ImGui::Text("Size: %d, %d", texsize.x, texsize.y);
              ImGui::Text("isSmooth: %s", (spr->tex.data().isSmooth()) ? "True" : "False");
              ImGui::Text("isSrgb: %s", (spr->tex.data().isSrgb()) ? "True" : "False");
              ImGui::Text("isRepeated: %s", (spr->tex.data().isRepeated()) ? "True" : "False");
              ImGui::Text("Native Handle: %ud", spr->tex.data().getNativeHandle());
              ImGui::TreePop();
            }
          }
        }

        void current_scene()
        {
          auto sc = scenes::current_scene();
          std::string tree_title = "Current Scene: " + sc->name;
          if(ImGui::TreeNode(tree_title.c_str()))
          {
            // list spaces in this scene
            auto sp_manager = sc->manager;
            for(auto& sp : sp_manager.spaces_)
            {
              if(ImGui::TreeNode(sp.first.c_str()))
              {
                // list objects in this space
                for(auto& obj : sp.second->objects_)
                {
                  if(ImGui::TreeNode(obj.first.c_str()))
                  {
                    // list components in object
                    for(auto& comp : obj.second->components_)
                    {
                      if(ImGui::TreeNode(comp.first.c_str()))
                      {
                        component_tree(comp);
                        ImGui::TreePop();
                      }
                    }        

                    ImGui::TreePop();
                  }
                }

                ImGui::TreePop();
              }
            }

            ImGui::TreePop();
          }
        }
      };

      namespace impl
      {
        bool show_debug_window = false;
        bool debug_ready_to_draw = false;

        imgui_listener listener;

        sf::Clock dclk;
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


      void render_imgui(sf::Time dt)
      {
        ImGui::SFML::Update(*graphics::get_window_manager().lock()->get_main_window().lock()->data().lock(), dt);
        impl::listener.run();
        impl::debug_ready_to_draw = true;
      }

      void present_imgui()
      {
        ImGui::SFML::Render(*graphics::get_window_manager().lock()->get_main_window().lock()->data().lock());
        impl::debug_ready_to_draw = false;
      }

    } // namespace debug
  }   // namespace core
} // namespace waifuengine