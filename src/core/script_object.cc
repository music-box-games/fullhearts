#include <script_object.hpp>
#include <utils.hpp>


namespace we = ::waifuengine;

namespace waifuengine
{
namespace core
{
namespace scripting
{

script_object::script_proxy::script_proxy(std::vector<std::string> * v) : v(v) {}
script_object::script_proxy::~script_proxy() {}

script_object::script_object()
{
  // run all init scripts
}

script_object::~script_object()
{
  // run all shutdown scripts
}

void script_object::update(float)
{
  // run all update scripts
}

void script_object::draw() const
{

}

script_object::script_proxy script_object::append_init()
{
  return script_proxy(&init_script);
}

script_object::script_proxy script_object::append_update()
{
  return script_proxy(&update_script);
}

script_object::script_proxy script_object::append_shutdown()
{
  return script_proxy(&shutdown_script);
}

} // namespace scripting
} // namespace core
} // namespace waifuengine
