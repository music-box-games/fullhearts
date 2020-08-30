#include <deque>
#include <array>
#include <string>
#include <cstring>

#include <boost/range/adaptor/reversed.hpp>
#include <imgui.h>

#include <debug.hpp>
#include <window.hpp>
#include <scenemanager.hpp>
#include <spacemanager.hpp>
#include <space.hpp>
#include <gameobject.hpp>
#include <component.hpp>
#include <scenes.hpp>
#include <scenelist.hpp>
#include <gameobject.hpp>
#include <scripting.hpp>

#include "shader.hpp"
#include "texture.hpp"
#include "events.hpp"
#include "event_manager.hpp"
#include "sprite.hpp"
#include "collider.hpp"
#include "mouse_collider.hpp"
#include "debug_draw.hpp"

#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

// TODO: forward declare tree functions in imgui_listener

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace core
  {
    namespace debug
    {

      static bool show_imgui_window = false;
      static bool imgui_render_ready = false;
      static bool fps_widget = false;
      static bool show_menu_bar = true;
      static bool use_console = false;

      constexpr int INPUT_BUFFER_LEN = 512;
      static char input_buffer[INPUT_BUFFER_LEN];

      

      class imgui_listener
      {
      public:
        waifuengine::scenes::impl::scene_manager *s;

      private:
        static const std::size_t HISTOGRAM_LEN = 300;
        std::deque<float> fps_histogram;

        void show_helper(const char *tip)
        {
          ImGui::TextDisabled("(?)");
          if (ImGui::IsItemHovered())
          {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(450.0f);
            ImGui::TextUnformatted(tip);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
          }
        }

        void window_tree(we::graphics::window_map const &ws)
        {
          if (ImGui::TreeNode("Windows"))
          {
            if(ImGui::TreeNode("ImGui"))
            {
              
              ImGui::TreePop();
            }
            for (auto w : ws)
            {
              if (ImGui::TreeNode(w.second->title.c_str()))
              {
                ImGui::Text("Window Width: %f", w.second->get_width());
                ImGui::Text("Window Height: %f", w.second->get_height());
                ImGui::TreePop();
              }
            }
            ImGui::TreePop();
          }
        }

        void raw_texture_data_tree(std::shared_ptr<we::graphics::raw_texture_data> const t)
        {
          if(ImGui::TreeNode("raw_texture_data"))
          {
            ImGui::Text("Texture Unit: %d", t->unit_id);
            ImGui::Text("glTexture Name: %d", t->txtr);
            ImGui::Text("Name: %s", t->name.c_str());
            ImGui::Text("Texture Width: %d", t->width);
            ImGui::Text("Texture Height: %d", t->height);
            ImGui::TreePop();
          }
        }

        void texture_tree(we::graphics::textures::texture const &t)
        {
          if (ImGui::TreeNode("Texture: %s", t.name.c_str()))
          {
            ImGui::Text("Name: %s", t.name.c_str());
            raw_texture_data_tree(t.tdata);
            ImGui::TreePop();
          }
        }

        void transform_tree_impl(we::graphics::transform * t)
        {
          float rot = t->rot_deg;
              if (ImGui::DragFloat("Rotation", &rot, 0.1f))
              {
                t->set_rotation(rot);
              }
              auto pos = t->get_position_in_world_coordinates();
              float trans_x = pos.x;
              float trans_y = pos.y;

              if (ImGui::DragFloat("Translation X", &trans_x, 1.f))
              {
                t->set_position_in_world_coordinates(graphics::world_point2d(trans_x, trans_y));
              }
              if (ImGui::DragFloat("Translation Y", &trans_y, 1.f))
              {
                t->set_position_in_world_coordinates(graphics::world_point2d(trans_x, trans_y));
              }
              float scale_x = t->scale_[0];
              float scale_y = t->scale_[1];
              if (ImGui::DragFloat("Scale X", &scale_x, 0.01f))
              {
                t->set_scale(glm::vec2(scale_x, scale_y));
              }
              if (ImGui::DragFloat("Scale Y", &scale_y, 0.01f))
              {
                t->set_scale(glm::vec2(scale_x, scale_y));
              }

              float width_ratio = t->width_ratio;
              float height_ratio = t->height_ratio;
              if(ImGui::DragFloat("Width Ratio", &width_ratio, 0.01f))
              {
                t->set_width_ratio(width_ratio);
              }
              if(ImGui::DragFloat("Height Ratio", &height_ratio, 0.01f))
              {
                t->set_height_ratio(height_ratio);
              }
        }

        void transform_tree(we::graphics::transform *t)
        {
          if (t)
          {
            if (ImGui::TreeNode("Transform"))
            {
              
                transform_tree_impl(t);

              ImGui::TreePop();
            }
          }
        }

        template <class Comp>
        void component_tree_t(Comp * c, std::string name)
        {
          if(c)
          {
            if(ImGui::TreeNode(Comp::NAME))
            {
              ImGui::TreePop();
            }
          }
        }

        template<>
        void component_tree_t(we::graphics::transform * tr, std::string name)
        {
          if(tr)
          {
            if(ImGui::TreeNode(graphics::transform::NAME))
            {
              ImGui::Text("Name: %s", name.c_str());
              transform_tree_impl(tr);
              ImGui::TreePop();
            }
          }
        }

        template<>
        void component_tree_t(we::graphics::debug_draw * dd, std::string name)
        {
          if(dd)
          {
            if(ImGui::TreeNode(graphics::debug_draw::NAME))
            {
              ImGui::Text("Name: %s", name.c_str());
              bool disable = dd->is_disabled();
              if(ImGui::Checkbox("Disable", &disable))
              {
                dd->disable(disable);
              }
              bool dbg = dd->is_debugging();
              if(ImGui::Checkbox("Debug", &dbg))
              {
                dd->debug(dbg);
              }
              if(ImGui::TreeNode("Attached Components"))
              {
                for(auto const& pair : dd->attached_components)
                {
                  if(ImGui::TreeNode(pair.first.c_str()))
                  {
                    ImGui::TreePop();
                  }
                }
                ImGui::TreePop();
              }
              ImGui::TreePop();
            }
          }
        }

        template<>
        void component_tree_t(we::physics::collider *c, std::string name)
        {
          if(c)
          {
            if(ImGui::TreeNode(physics::collider::NAME))
            {
              ImGui::Text("Name: %s", name.c_str());
              bool disable = c->is_disabled();
              if(ImGui::Checkbox("Disable", &disable))
              {
                c->disable(disable);
              }
              bool dbg = c->is_debugging();
              if(ImGui::Checkbox("Debug", &dbg))
              {
                c->debug(dbg);
              }
              ImGui::TreePop();
            }
          }
        }

        template <>
        void component_tree_t(we::graphics::sprite *s, std::string name)
        {
          if (s)
          {
            if (ImGui::TreeNode(graphics::sprite::NAME))
            {
              ImGui::Text("Name: %s", name.c_str());
              bool disable = s->is_disabled();
              if(ImGui::Checkbox("Disable", &disable))
              {
                s->disable(disable);
              }
              bool dbg = s->is_debugging();
              if(ImGui::Checkbox("Debug", &dbg))
              {
                s->debug(dbg);
              }
              texture_tree(s->tex);
              bool parent_lock = s->transform_locked_to_parent();
              if(ImGui::Checkbox("Lock Tranform to Parent", &parent_lock))
              {
                s->lock_transform_to_parent_transform(parent_lock);
              }
              if(!parent_lock)
              {
                transform_tree(&s->trans);
              }
              ImGui::TreePop();
            }
          }
        }

        void component_tree(std::pair<std::string const, std::shared_ptr<we::components::_impl::_base_component>> c)
        {

          // TODO find a better way to do this for sure like a switch/ifelse with the name and then dyanmic cast it there
          we::graphics::sprite *sp = dynamic_cast<we::graphics::sprite *>(c.second.get());
          if (sp)
          {
            component_tree_t(sp, c.first);
            return;
          }
          we::physics::collider * col = dynamic_cast<we::physics::collider *>(c.second.get());
          if(col)
          {
            component_tree_t(col, c.first);
            return;
          }
          we::graphics::debug_draw * dd = dynamic_cast<we::graphics::debug_draw *>(c.second.get());
          if(dd)
          {
            component_tree_t(dd, c.first);
            return;
          }
          we::graphics::transform * tr = dynamic_cast<we::graphics::transform *>(c.second.get());
          if(tr)
          {
            component_tree_t(tr, c.first);
            return;
          }
          we::ui::mouse_collider * mscol = dynamic_cast<we::ui::mouse_collider *>(c.second.get());
          if(mscol)
          {
            component_tree_t(mscol, c.first);
            return;
          }

          
          {
            if (ImGui::TreeNode(c.first.c_str()))
            {
              ImGui::TreePop();
            }
          }
        }

        // TODO: template overloads of this for graphics prims maybe
        void object_tree(std::pair<std::string const, std::shared_ptr<we::object_management::gameobject>> &obj, std::shared_ptr<we::object_management::space> sp = {})
        {
          if (obj.second.use_count())
          {
            if (ImGui::TreeNode(obj.first.c_str()))
            {
              bool disable = obj.second->disabled();
              if(ImGui::Checkbox("Disable", &disable))
              {
                obj.second->disable(disable);
              }
              auto * debug_rect_test = dynamic_cast<graphics::primatives::rectangle *>(obj.second.get());
              if(debug_rect_test)
              {
                ImGui::Text("Width: %f", debug_rect_test->width);
                ImGui::Text("Height: %f", debug_rect_test->height);
                ImGui::Text("Center: (%f, %f)", static_cast<float>(debug_rect_test->center.x), static_cast<float>(debug_rect_test->center.y));
              }
              if (ImGui::TreeNode("Components"))
              {
                ImGui::Text("Count: %d", obj.second->components_.size());
                auto &comps = obj.second->components_;
                for (auto c : comps)
                {
                  component_tree(c);
                }
                ImGui::TreePop();
              }
              ImGui::TreePop();
            }
          }
        }

        void object_list(std::shared_ptr<we::object_management::space> &sp)
        {
          auto pt = we::utils::get_game_save_data_folder().append("objects");
          auto obj_list = we::object_management::gameobject::get_object_list();
          std::vector<const char *> names;
          for (auto &pair : obj_list)
          {
            names.push_back(pair.first.c_str());
          }
          static int current_object_index = 0;
          if (current_object_index > names.size())
            current_object_index = 0;
          ImGui::ListBox("Objects", &current_object_index, names.data(), static_cast<int>(names.size()));
          if (ImGui::Button("Load"))
          {
            sp->load_object(names[current_object_index]);
          }
          ImGui::SameLine();
          if (ImGui::Button("Delete"))
          {
            fs::remove(pt.append(names[current_object_index]));
          }
        }

        void space_tree(std::pair<std::string const, std::shared_ptr<we::object_management::space>> &sp, we::object_management::space_manager *spm)
        {
          if (sp.second.use_count())
          {

            if (ImGui::TreeNode(sp.first.c_str()))
            {

              auto &obj = sp.second->objects_;
              for (auto &o : obj)
              {
                object_tree(o, sp.second);
              }
              ImGui::TreePop();
            }
          }
        }

        void scene_tree(std::shared_ptr<we::scenes::scene> sc)
        {
          if (sc.use_count())
          {
            if (ImGui::TreeNode(sc->name.c_str()))
            {
              auto *spmanager = sc->get_manager();
              auto &sps = spmanager->spaces_;
              // input to add new space

              for (auto &sp : sps)
              {
                space_tree(sp, spmanager);
              }
              ImGui::TreePop();
            }
          }
        }

        void menu_bar()
        {
          if (ImGui::BeginMainMenuBar())
          {

            ImGui::EndMainMenuBar();
          }
        }

        void fps()
        {
          auto fps_impl_func = [this]() -> void {
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
            //ImGui::PlotHistogram("Framerate", values.data(), static_cast<int>(HISTOGRAM_LEN), 0, NULL, 0.0f, 1.0f, ImVec2(300,80));
            // slider for max frame rate
            //ImGui::DragScalar("Frame Limit", ImGuiDataType_::ImGuiDataType_U16, &we::core::settings::frame_limit, 1.0f);
          };

          if (fps_widget)
          {
            if (!ImGui::Begin("FPS"))
            {
              ImGui::End();
            }
            else
            {
              fps_impl_func();
              ImGui::End();
            }
          }
          else
          {
            fps_impl_func();
          }
        }

        void scene_list()
        {
          auto sc_list = we::scenes::impl::scene_manager::get_scene_list();
          std::vector<const char *> names;
          for (auto &p : sc_list)
          {
            names.push_back(p.first.c_str());
          }
          static int current_scene_index = 0;
          if (current_scene_index > names.size())
            current_scene_index = 0;
          ImGui::ListBox("Scenes", &current_scene_index, names.data(), static_cast<int>(names.size()));
          if (ImGui::Button("Load Scene"))
          {
            s->load(names[current_scene_index]);
          }
          ImGui::SameLine();
          if (ImGui::Button("Unload Scene"))
          {
            s->unload();
          }
        }

        void shader_list()
        {
          if (ImGui::TreeNode("Shaders"))
          {
            std::vector<std::string> list = we::graphics::shaders::list_loaded_shaders();
            for (auto const &s : list)
            {
              ImGui::Text(s.c_str());
            }
            ImGui::TreePop();
          }
        }

        void image_list()
        {
          if (ImGui::TreeNode("Images"))
          {
            if (ImGui::TreeNode("Files"))
            {
              auto file_list = we::graphics::textures::list_image_files();
              for(auto const& s : file_list)
              {
                ImGui::Text("%s", s.c_str());
              }
              ImGui::TreePop();
            }
            if (ImGui::TreeNode("Loaded"))
            {
              auto list = we::graphics::textures::list_loaded_images();
              for (auto const &s : list)
              {
                ImGui::Text("%s", s.c_str());
              }
              ImGui::TreePop();
            }
            ImGui::TreePop();
          }
        }

        void texture_list()
        {
          if (ImGui::TreeNode("Loaded Textures"))
          {
            auto tmap = we::graphics::textures::get_texturemap();
            for (auto const &pair : tmap)
            {
              
              raw_texture_data_tree(pair.second);
            }
            ImGui::TreePop();
          }
        }

        void console()
        {
          if (true)
            return;
          static std::deque<std::string> history;
          static std::deque<std::string> log;

          static bool scroll_lock = true;

          constexpr int HISTORY_LEN = 100;
          constexpr int LOG_LEN = 100;

          auto push_log = [&LOG_LEN](std::string const &s) -> void {
            if (log.size() == LOG_LEN)
            {
              log.pop_back();
            }
            log.push_front(s);
          };

          auto push_command = [&push_log](std::string const &s) -> void {
            push_log(std::string(">") + s);
          };

          auto clear_log = []() -> void {
            log.clear();
          };

          if (use_console)
          {
            ImGui::SetNextWindowSize(ImVec2(520, 400), ImGuiCond_FirstUseEver);
            if (!ImGui::Begin("Console"))
            {
              ImGui::End();
            }
            else
            {
              // scroll box
              ImGui::BeginChild("Scrolling Region", ImVec2(0, 200), false, ImGuiWindowFlags_HorizontalScrollbar);
              for (std::string const &s : boost::adaptors::reverse(log))
              {
                ImGui::TextWrapped(s.c_str());
              }
              if (scroll_lock)
              {
                ImGui::SetScrollHereY(1.0f);
              }
              ImGui::EndChild();
              ImGui::Separator();
              ImGui::Checkbox("Lock To Bottom", &scroll_lock);
              if (ImGui::Button("Test"))
              {
                push_log("test");
              }
              ImGui::SameLine();
              if (ImGui::Button("Clear"))
              {
                clear_log();
              }
              // text input
              if (ImGui::InputText("Input", input_buffer, INPUT_BUFFER_LEN, ImGuiInputTextFlags_EnterReturnsTrue))
              {
                push_command(input_buffer);
                // pass command to interpreter and print output
                auto result = we::core::scripting::interpret(input_buffer, we::core::scripting::interpreter_mode::debug);
                if (result)
                {
                  push_log(result.value());
                }
                std::memset(input_buffer, 0, INPUT_BUFFER_LEN);
                ImGui::SetKeyboardFocusHere(0);
              }
              ImGui::End();
            }
          }
        }

      public:
        imgui_listener() : s(nullptr)
        {
          std::memset(input_buffer, 0, INPUT_BUFFER_LEN);

        }

        ~imgui_listener() {}

        void attach(waifuengine::scenes::impl::scene_manager *sm) { s = sm; }
        void detach() { s = nullptr; }

        void tree()
        {
          fps();
          // toggle to put frame rate in separate window
          ImGui::Checkbox("Show FPS In Separate Window", &fps_widget);
          // mouse
          double mx, my;
          glfwGetCursorPos(graphics::get_current_window()->get(), &mx, &my);
          ImGui::Text("Mouse Pos: %f, %f", mx, my);
          // console

          // window info
          window_tree(we::graphics::get_window_list());

          // make a tree for each scene present in the attached scene_manager
          // right now there's always one
          auto sc = s->current_scene();
          scene_tree(sc);

          shader_list();
          image_list();
          texture_list();
        }

        void draw()
        {
          ImGui::Begin("Debug");
          ImGui::SetWindowFontScale(2);

          menu_bar();
          tree();
          ImGui::End();
        }
      };

      static imgui_listener listener;

      void init_imgui()
      {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.IniFilename = NULL;

        ImGui::StyleColorsDark(); // dark mode ayo

        // set up renderer and wrangler bindings
        auto last_window = we::graphics::get_last_window_created();
        ImGui_ImplGlfw_InitForOpenGL(last_window->get(), true);
        ImGui_ImplOpenGL3_Init("#version 330");

        listener.attach(we::scenes::impl::smanager);
      }

      void shutdown_imgui()
      {
        listener.detach();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
      }

      void toggle_imgui_window()
      {
        show_imgui_window = !show_imgui_window;
        we::graphics::window::apply_imgui_restriction(show_imgui_window);
      }

      void render_imgui()
      {
        if (show_imgui_window)
        {
          ImGui_ImplOpenGL3_NewFrame();
          ImGui_ImplGlfw_NewFrame();
          ImGui::NewFrame();

          listener.draw();
          imgui_render_ready = true;
        }
      }

      void present_imgui()
      {
        if (imgui_render_ready)
        {
          ImGui::Render();
          ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
          imgui_render_ready = false;
        }
      }
    } // namespace debug
  }   // namespace core
} // namespace waifuengine