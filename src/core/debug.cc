#include <imgui.h>

#include <debug.hpp>
#include <window.hpp>

#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

namespace we = ::waifuengine;

namespace waifuengine
{
namespace core
{
namespace debug
{

static bool show_imgui_window = false;

void init_imgui()
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;

  ImGui::StyleColorsDark(); // dark mode ayo

  // set up renderer and wrangler bindings
  auto last_window = we::graphics::get_last_window_created();
  ImGui_ImplGlfw_InitForOpenGL(last_window->get(), true);
  ImGui_ImplOpenGL3_Init("#version 330");
}

void shutdown_imgui()
{
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
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  // window
  ImGui::Begin("Debug Tools");
  ImGui::Text("Test");
  ImGui::End();

  ImGui::Render();
}

void present_imgui()
{
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

} // namespace debug
} // namespace core
} // namespace waifuengine