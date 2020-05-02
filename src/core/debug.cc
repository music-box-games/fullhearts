#include <queue>
#include <array>

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

#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

namespace we = ::waifuengine;

namespace waifuengine
{
namespace core
{
namespace debug
{
static bool edit_mode_enabled = false;
static bool show_imgui_window = false;
static bool imgui_render_ready = false;
static bool fps_widget = false;
static bool show_menu_bar = true;


class imgui_listener
{
public:
  waifuengine::scenes::impl::scene_manager *s;

private:
  static const std::size_t HISTOGRAM_LEN = 300;
  std::deque<float> fps_histogram;

  void show_helper(const char * tip)
  {
    ImGui::TextDisabled("(?)");
    if(ImGui::IsItemHovered())
    {
      ImGui::BeginTooltip();
      ImGui::PushTextWrapPos(450.0f);
      ImGui::TextUnformatted(tip);
      ImGui::PopTextWrapPos();
      ImGui::EndTooltip();
    }
  }

  void object_tree(std::pair<std::string const, std::shared_ptr<we::object_management::gameobject>>& obj, std::shared_ptr<we::object_management::space> sp)
  {
    if (obj.second.use_count())
    {

    if(ImGui::TreeNode(obj.first.c_str()))
    {
      ImGui::TreePop();
    }
    }
  }

  void space_tree(std::pair<std::string const, std::shared_ptr<we::object_management::space>>& sp,  we::object_management::space_manager * spm)
  {
    if (sp.second.use_count())
    {

    if(ImGui::TreeNode(sp.first.c_str()))
    {
      auto& obj = sp.second->objects_;
      for(auto& o : obj)
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
    if(ImGui::TreeNode(sc->name.c_str()))
    {
      auto * spmanager = sc->get_manager();
      auto& sps = spmanager->spaces_;
      
      for(auto& sp : sps)
      {
        space_tree(sp, spmanager);
      }
      ImGui::TreePop();
    }
    }
  }

  void menu_bar()
  {
    if(ImGui::BeginMainMenuBar())
    {
      if(ImGui::BeginMenu("Editor"))
      {
        char new_scene_buf[256] {'\0'};
        if (ImGui::InputText("New Scene", new_scene_buf, 256, ImGuiInputTextFlags_EnterReturnsTrue))
        {
          s->blank_scene(new_scene_buf);
          edit_mode_enabled = true;
        }

        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }
  }

  void fps()
  {
    auto fps_impl_func = [this]() -> void
    {
      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      fps_histogram.push_back(ImGui::GetIO().Framerate);
      if(fps_histogram.size() > HISTOGRAM_LEN)
      {
        fps_histogram.pop_front();
      }
      static std::array<float, HISTOGRAM_LEN> values;
      std::copy(fps_histogram.begin(), fps_histogram.end(), values.begin());
      std::stringstream ss;
      ss << "Framerate\n(Last " << HISTOGRAM_LEN << " frames)\nLimit: " << we::core::settings::frame_limit;
      ImGui::PlotLines(ss.str().c_str(), values.data(), HISTOGRAM_LEN, 0, NULL, 0, 144, ImVec2(0,0), 4);
      //ImGui::PlotHistogram("Framerate", values.data(), static_cast<int>(HISTOGRAM_LEN), 0, NULL, 0.0f, 1.0f, ImVec2(300,80));
      // slider for max frame rate
      ImGui::DragScalar("Frame Limit", ImGuiDataType_::ImGuiDataType_U16, &we::core::settings::frame_limit, 1.0f);
    };

    if(fps_widget)
    {
      if(!ImGui::Begin("FPS"))
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
    for(auto& p : sc_list)
    {
      names.push_back(p.first.c_str());
    }
    static int current_scene_index = 0;
    if(current_scene_index > names.size()) current_scene_index = 0;
    ImGui::ListBox("Scenes", &current_scene_index, names.data(), static_cast<int>(names.size()));
    if(ImGui::Button("Load Scene"))
    {
      s->load(names[current_scene_index]);
    }
    if (ImGui::Button("Unload Scene"))
    {
      s->unload();
    }
    if (ImGui::Button("Delete Scene"))
    {
      fs::remove(sc_list[names[current_scene_index]]);
    }
  }

public:

  imgui_listener() : s(nullptr) {}
  ~imgui_listener() {}

  void attach(waifuengine::scenes::impl::scene_manager *sm) { s = sm; }
  void detach() { s = nullptr; }

  void tree()
  {
    scene_list();
    fps();
    // toggle to put frame rate in separate window
    ImGui::Checkbox("Show FPS In Separate Window", &fps_widget);
    // toggle for edit mode
    ImGui::Checkbox("Enable Editing", &edit_mode_enabled);
    // save current scene
    if(ImGui::Button("Save"))
    {
      s->save();
    }

    // make a tree for each scene present in the attached scene_manager
    // right now there's always one
    auto sc = s->current_scene();
    scene_tree(sc);
  }

  void draw()
  {
    ImGui::Begin("Debug");
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
  (void)io;

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
} // namespace core
} // namespace waifuengine