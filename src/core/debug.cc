#include <deque>
#include <array>
#include <string>
#include <cstring>

#include <boost/range/adaptor/reversed.hpp>
#include <imgui.h>
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

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

// TODO: forward declare tree functions in imgui_listener or something

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace core
  {
    namespace debug
    {
      void init_imgui()
      {

      }

      void shutdown_imgui()
      {
        
      }

      void render_imgui()
      {

      }

      void present_imgui()
      {

      }

      void imgui_start_frame()
      {
        
      }
    } // namespace debug
  }   // namespace core
} // namespace waifuengine