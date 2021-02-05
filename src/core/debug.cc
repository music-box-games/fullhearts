#include <deque>
#include <array>
#include <string>
#include <cstring>
#include <bitset>

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
#include "button.hpp"

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
          font_manager_tree();
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

        void font_manager_tree()
        {
          if(ImGui::TreeNode("Font Manager"))
          {
            auto fman = graphics::get_font_manager().lock();
            if(!fman.use_count())
            {
              ImGui::TreePop();
              return;
            }
            ImGui::Text("Font count: %d", fman->count());

            // load new font
            
            // list loaded fonts and allow unloading fonts
            if(ImGui::TreeNode("Loaded Fonts"))
            {
              for(auto& f : fman->fonts_)
              {
                ImGui::Text(f.second->name().c_str());
                ImGui::SameLine();
                if(ImGui::Button("Unload"))
                {
                  fman->unload_font(f.first);
                }
              }
              ImGui::TreePop();
            }
            ImGui::TreePop();
          }
        }

        

        void transform_tree(graphics::transform & t)
        {
          // translation
          auto trans = t.translation();
          int trans_x = static_cast<int>(trans.x), trans_y = static_cast<int>(trans.y);
          if(ImGui::DragInt("Translation X", &trans_x, 1))
          {
            t.set_translation(trans_x, trans_y);
          }
          if(ImGui::DragInt("Translation Y", &trans_y, 1))
          {
            t.set_translation(trans_x, trans_y);
          }
          // scale
          auto scl = t.scale();
          float scl_x = scl.x, scl_y = scl.y;
          if(ImGui::DragFloat("Scale X", &scl_x, 0.1f))
          {
            t.set_scale(scl_x, scl_y);
          }
          if(ImGui::DragFloat("Scale Y", &scl_y, 0.1f))
          {
            t.set_scale(scl_x, scl_y);
          }
          // rotation
          float rot = t.rotation();
          if(ImGui::DragFloat("Rotation", &rot, 0.1f))
          {
            t.set_rotation(rot);
          }
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

        void sftransform_tree(sf::Transformable& trans)
        {
          // translation
          sf::Vector2f const& pos = trans.getPosition();
          float posx = pos.x, posy = pos.y;
          if(ImGui::DragFloat("Position X", &posx, 1.f))
          {
            trans.setPosition(posx, posy);
          }
          if(ImGui::DragFloat("Position Y", &posy, 1.f))
          {
            trans.setPosition(posx, posy);
          }
          // scale
          sf::Vector2f const& sc = trans.getScale();
          float scx = sc.x, scy = sc.y;
          if(ImGui::DragFloat("Scale X", &scx, 1.f))
          {
            trans.setScale(scx, scy);
          }
          if(ImGui::DragFloat("Scale Y", &scy, 1.f))
          {
            trans.setScale(scx, scy);
          }
          // rotation
          float rot = trans.getRotation();
          if(ImGui::DragFloat("Rotation", &rot, 1.f))
          {
            trans.setRotation(rot);
          }
        }

        void text_tree(graphics::text& tobj)
        {
          std::stringstream ss;
          ss << "Style: " << std::bitset<8>(tobj.style_);
          ImGui::Text(ss.str().c_str());
          ImGui::Text("Font: %s", tobj.get_font().c_str());
          ImGui::Text("Character Size: %d", tobj.get_char_size_in_pixels());
          auto currentc = tobj.get_active_color();
          auto idlefc = tobj.get_fill_color_idle();
          auto hoverfc = tobj.get_fill_color_hover();
          auto infc = tobj.get_fill_color_inactive();
          ImGui::Text("Active Fill Color: %u, %u, %u, %u", currentc.r, currentc.g, currentc.b, currentc.a);
          ImGui::Text("Idle Fill Color: %u, %u, %u, %u", idlefc.r, idlefc.g, idlefc.b, idlefc.a);
          ImGui::Text("Hover Fill Color: %u, %u, %u, %u", hoverfc.r, hoverfc.g, hoverfc.b, hoverfc.a);
          ImGui::Text("Inactive Fill Color: %u, %u, %u, %u", infc.r, infc.g, infc.b, infc.a);
          ImGui::Text("String: %s", tobj.get_string().c_str());
          // text transform (different from graphics::transform)
          sftransform_tree(tobj.tobj_);
          
        }

        void textbutton_object_tree(std::shared_ptr<ui::text_button> & obj)
        {
          if(ImGui::TreeNode("Text Object"))
          {
            text_tree(obj->tobj_);
            ImGui::TreePop();
          }
        }

        void button_object_tree(std::shared_ptr<ui::button> & obj)
        {
          // stuff

          {
            std::shared_ptr<ui::text_button> tbptr = std::dynamic_pointer_cast<ui::text_button, ui::button>(obj);
            if(tbptr.use_count())
            {
              textbutton_object_tree(tbptr);
            }
          }
        }

        void gameobject_tree(std::pair<const std::string, std::shared_ptr<object_management::gameobject>> & obj)
        {
          ImGui::Text("Name: %s", obj.first.c_str());
          if(ImGui::TreeNode("Transform"))
          {
            transform_tree(obj.second->object_transform);
            ImGui::TreePop();
          }
          for(auto& comp : obj.second->components_)
          {
            if(ImGui::TreeNode(comp.first.c_str()))
            {
              component_tree(comp);
              ImGui::TreePop();
            }
          }

          {
            std::shared_ptr<ui::button> bptr = std::dynamic_pointer_cast<ui::button, object_management::gameobject>(obj.second);
            if(bptr.use_count())
            {
              button_object_tree(bptr);
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
                    gameobject_tree(obj);
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