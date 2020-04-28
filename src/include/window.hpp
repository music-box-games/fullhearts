#ifndef _WE_WINDOW_HPP_
#define _WE_WINDOW_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

#include <settings.hpp>

namespace waifuengine
{
  namespace graphics
  {
    typedef std::string window_id_type;
    class window
    {
    public:
      using window_ptr = GLFWwindow *;
      window(std::string title, int width, int height);
      window(std::string title, window_ptr w); // TODO: this is uhhhhhhhhhhh
      ~window();

      void update(float dt);
      void draw() const;

      window_ptr get();
      window_id_type get_id() const;

      explicit operator bool() const;

    private:
      window_ptr data;
      window_id_type id;

      std::string title;
      int width;
      int height;
    };


    std::shared_ptr<window> get_current_window();
    std::shared_ptr<window> get_window_by_id(window_id_type id);

    std::shared_ptr<window> create_window(std::string title, int width = waifuengine::core::settings::window_width, int height = waifuengine::core::settings::window_height);
  }
}

#endif