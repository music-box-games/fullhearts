#include <iostream>
#include <unordered_map>

#include <window.hpp>
#include <settings.hpp>
#include <utils.hpp>

namespace we = ::waifuengine;
namespace settings = we::core::settings;

namespace waifuengine
{
namespace graphics
{

namespace impl
{
static std::unordered_map<we::graphics::window_id_type, std::shared_ptr<we::graphics::window>> windows;

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
} // namespace impl

window::window(std::string t, int w, int h) : title(t), width(w), height(h)
{
  glfwWindowHint(GLFW_SAMPLES, 4); // 4x AA
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 3.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 3
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // to make Macs happy
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // make sure to get core profile

  data = glfwCreateWindow(settings::window_width, settings::window_height, title.c_str(), NULL, NULL);
  if(data == NULL) // mmm yum yum c
  {
    // TODO: update to proper logging
    std::cerr << "Failed to open GLFW window" << std::endl;
  }
  id = impl::get_fresh_id<window_id_type>();
}

window::window(std::string title, window::window_ptr w)
{
  // TODO: secure this against nullptr
  data = w;
  // gen id
}

window::~window()
{

}

void window::update(float)
{

}

void window::draw() const
{

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
  return {};
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

std::shared_ptr<window> create_window(std::string title, int width, int height)
{
  std::shared_ptr<window> ptr {new window(title, width, height)};
  impl::windows[ptr->get_id()] = ptr;
  return ptr;
}


} // namespace graphics
} // namespace waifuengine