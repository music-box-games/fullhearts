#include <iostream>
#include <unordered_map>
#include <set>

#include <window.hpp>
#include <settings.hpp>
#include <utils.hpp>
#include <engine.hpp>
#include <input.hpp>
#include <event_manager.hpp>

namespace we = ::waifuengine;
using settings = we::core::settings;

namespace waifuengine
{
namespace graphics
{

namespace impl
{
static std::set<we::graphics::window_id_type> marked_for_close;
static window_map windows;
static std::unordered_map<we::graphics::window::window_ptr, std::shared_ptr<we::graphics::window>> underlying_windows;
static we::graphics::window_id_type last_window = we::graphics::window_id_type{};



template<class id_type>
id_type get_fresh_id()
{
  if(typeid(id_type) == typeid(std::string))
  {
    std::string id;
    while(windows.count(id = we::utils::generate_string())) {}
    return id;
  }
  return id_type();
}

static void key_callback(window::window_ptr window, int key, int scancode, int action, int mods)
{
  impl::underlying_windows.at(window)->queue_input(key, action);
}

} // namespace impl

bool window::imgui_restriction = false;

void framebuffer_size_callback(window::window_ptr w, int width, int height)
{
  // TODO: maybe a flag to switch between using .at and [] and also exception handling
  impl::underlying_windows.at(w)->resize(width, height);

}

void window::queue_input(int key, int action)
{
  queued_inputs.push_back({key, action});
}

window::window(std::string t, int w, int h) : title(t), width(w), height(h)
{
  glfwWindowHint(GLFW_SAMPLES, 4); // 4x AA
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // 3.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // 3
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // to make Macs happy
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // make sure to get core profile
  glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE); // double buffer

  data = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  glfwMakeContextCurrent(data);
  glfwSwapInterval(0); // turn off frame limit
  if(data == NULL) // mmm yum yum c
  {
    // TODO: update to proper logging
    std::cerr << "Failed to open GLFW window" << std::endl;
  }
  id = impl::get_fresh_id<window_id_type>();
  glfwSetWindowSizeCallback(data, framebuffer_size_callback);
  
}

window::window(std::string title, window::window_ptr w)
{
  // TODO: secure this against nullptr
  data = w;
  // gen id
}

window::~window()
{
  glfwDestroyWindow(data);
}

void window::clear()
{
  glfwMakeContextCurrent(data);
  glfwPollEvents();
  // if window should close and it's the only window open,
  // shutdown the game
  // otherwise just marked the class to be deleted on next loop
  if(glfwWindowShouldClose(data))
  {
    if(impl::windows.size() == 1)
    {
      we::core::engine::shutdown();
    }
    else
    {
      mark_window_to_close(id);
    }
  }
  glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void window::present() const
{
  glfwSwapBuffers(data);
}

void window::apply_imgui_restriction(bool set)
{
  imgui_restriction = set;
}

void window::process_input()
{
  for(auto& pair : queued_inputs)
  {
    we::graphics::input::input_event e;
    e.k = input::impl::keyset[pair.first];
    e.a = input::impl::actionset[pair.second];
    e.w = id;
    if(imgui_restriction)
    {
    if(e.k == input::key::grave_accent)
    {
      we::events::handle(&e);
    }
    }
    else
    {
      we::events::handle(&e);
    }
  }
  queued_inputs.clear();
}

void window::resize(int w, int h)
{
  width = w;
  height = h;
  glfwMakeContextCurrent(data);
  glViewport(0, 0, width, height);
}

// also deletes windows that are marked
void window::clear_all()
{
  // delete windows marked to close
  for(auto id : impl::marked_for_close)
  {
    impl::underlying_windows.erase(impl::windows[id]->data);
    impl::windows.erase(id);
  }
  impl::marked_for_close.clear();

  for(auto w : impl::windows)
  {
    w.second->clear();
  }
}

void window::present_all()
{
  for(auto w : impl::windows)
  {
    w.second->present();
  }
}

void window::process_all_input()
{
  for(auto w : impl::windows)
  {
    w.second->process_input();
  }
}

float window::get_width() const
{
  return static_cast<float>(width);
}

float window::get_height() const
{
  return static_cast<float>(height);
}

window::window_ptr window::get()
{
  return data;
}

window_id_type window::get_id() const
{
  return id;
}

window::operator bool() const
{
  return !(data == NULL);
}

std::shared_ptr<window> get_current_window() 
{
  return (*impl::windows.begin()).second;
}

std::shared_ptr<window> get_window_by_id(window_id_type id)
{
  if(impl::windows.count(id))
  {
    return impl::windows[id];
  }
  else
  {
    return {};
  }
}

std::shared_ptr<window> get_last_window_created()
{
  if(impl::windows.count(impl::last_window))
  {
    return impl::windows[impl::last_window];
  }
  else
  {
    return {};
  }
}

std::shared_ptr<window> create_window(std::string title, int width, int height)
{
  we::core::settings::write_t<int>("window_width", width);
  we::core::settings::write_t<int>("window_height", height);
  std::shared_ptr<window> ptr {new window(title, width, height)};
  impl::windows[ptr->id] = ptr;
  impl::underlying_windows[ptr->data] = ptr;
  impl::last_window = ptr->id;
  glfwSetKeyCallback(ptr->data, impl::key_callback);
  return ptr;
}

void mark_window_to_close(window_id_type id)
{
  impl::marked_for_close.insert(id);
}

void mark_all_windows_to_close()
{
  for(auto& pair : impl::windows)
  {
    mark_window_to_close(pair.first);
  }
}

void close_all_windows()
{
  impl::underlying_windows.clear();
  impl::windows.clear();
}

window_map const& get_window_list()
{
  return impl::windows;
}


} // namespace graphics
} // namespace waifuengine
