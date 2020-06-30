#ifndef _WE_WINDOW_HPP_
#define _WE_WINDOW_HPP_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <queue>
#include <utility> //std::pair

#include <settings.hpp>

#include "debug.hpp"

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

      void clear();
      void present() const;
      void process_input();

      window_ptr get();
      window_id_type get_id() const;

      void resize(int width, int height);

      explicit operator bool() const;

      static void clear_all();
      static void present_all();
      static void process_all_input();

      void queue_input(int key, int action);

      float get_width() const;
      float get_height() const;

      static void apply_imgui_restriction(bool set);

    private:
      friend std::shared_ptr<window> create_window(std::string, int, int);
      friend class waifuengine::core::debug::imgui_listener;

      window_ptr data;
      window_id_type id;

      std::string title;
      int width;
      int height;

      static bool imgui_restriction;

      std::deque<std::pair<int, int>> queued_inputs;
    };
    using window_map = std::unordered_map<waifuengine::graphics::window_id_type, std::shared_ptr<waifuengine::graphics::window>>;


    std::shared_ptr<window> get_current_window();
    std::shared_ptr<window> get_window_by_id(window_id_type id);
    std::shared_ptr<window> get_last_window_created();

    window_map const& get_window_list();

    std::shared_ptr<window> create_window(std::string title, int width = waifuengine::core::settings::read_t<int>("window_width"), int height = waifuengine::core::settings::read_t<int>("window_height"));

    void mark_window_to_close(window_id_type id);
    void mark_all_windows_to_close();
    void close_all_windows();
  }
}

#endif