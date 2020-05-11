#ifndef _WE_SCRIPT_OBJECT_HPP_
#define _WE_SCRIPT_OBJECT_HPP_

#include <string>
#include <sstream>
#include <vector>

#include <script_object.hpp>
#include <serialization.hpp>
#include <component.hpp>
#include <utils.hpp>

namespace waifuengine
{
namespace core
{
namespace debug
{
class imgui_listener;
}
} // namespace core
namespace core
{
namespace scripting
{
class script_object : public waifuengine::components::component<script_object>
{
private:
  friend class waifuengine::core::debug::imgui_listener;
  std::vector<std::string> init_script;
  std::vector<std::string> update_script;
  std::vector<std::string> shutdown_script;
  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive &ar, unsigned int const)
  {
    ar.template register_type<script_object>();
    ar & boost::serialization::base_object <waifuengine::components::component<script_object>>(*this);
    ar & init_script;
    ar & update_script;
    ar & shutdown_script;
  }

public:
  COMPONENT_NAME(script_object);
  COMPONENT_TYPE(script_object);

  class script_proxy
  {
  private:
    std::vector<std::string> *v;

  public:
    script_proxy(std::vector<std::string> *v);
    ~script_proxy();

    template <class input>
    script_proxy &operator<<(input &i)
    {
      v->push_back(i);
      return *this;
    }
    template <>
    script_proxy& operator<<(std::stringstream &ss)
    {
      v->push_back(ss.str());
      return *this;
    }

    template <>
    script_proxy& operator<<(std::wstring &s)
    {
      v->push_back(we::utils::wide_string_to_mb(s));
      return *this;
    }

    template <>
    script_proxy& operator<<(std::wstringstream &ss)
    {
      v->push_back(we::utils::wide_string_to_mb(ss.str()));
      return *this;
    }
  };

  script_object();
  ~script_object();

  void update(float dt);
  void draw() const;

  script_proxy append_init();
  script_proxy append_update();
  script_proxy append_shutdown();
};
} // namespace scripting
} // namespace core
} // namespace waifuengine

BOOST_CLASS_EXPORT_KEY(waifuengine::core::scripting::script_object);

#endif