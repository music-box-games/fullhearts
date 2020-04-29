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

class imgui_listener
{
public:
  waifuengine::scenes::impl::scene_manager *s;

  imgui_listener() : s(nullptr) {}
  ~imgui_listener() {}

  void attach(waifuengine::scenes::impl::scene_manager *sm) { s = sm; }
  void detach() { s = nullptr; }

  void draw()
  {
    // make a tree for each scene present in the attached scene_manager
    // right now there's always one
    auto sc = s->current_scene();
    if (ImGui::TreeNode(sc->name.c_str()))
    {
      // get space manager
      auto *spmanager = sc->get_manager();
      // get spaces
      auto &sps = spmanager->spaces_;
      //  tree node for each space
      for (auto &sp : sps)
      {
        if (ImGui::TreeNode(sp.first.c_str()))
        {
          // get each object
          auto &objects = sp.second->objects_;
          // tree node for each object
          for (auto &obj : objects)
          {
            if (ImGui::TreeNode(obj.first.c_str()))
            {
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

static bool show_imgui_window = false;
static imgui_listener listener;
static bool imgui_render_ready = false;

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

    if (!ImGui::Begin("Debug Tools"))
    {
      ImGui::End();
    }
    else
    {
      listener.draw();
      ImGui::End();
    }
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