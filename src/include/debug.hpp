#ifndef _WE_DEBUG_HPP_
#define _WE_DEBUG_HPP_

namespace waifuengine
{
  namespace scenes
  {
    namespace impl
    {
      class scene_manager; // forward decl
    }
  }

  namespace core
  {
    namespace debug
    {
      void init_imgui();
      void shutdown_imgui();
      void toggle_imgui_window();

      void render_imgui();
      void present_imgui();
      void imgui_start_frame();

      class imgui_listener;
    }
  }
}

#endif