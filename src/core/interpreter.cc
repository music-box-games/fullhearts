#include <any>
#include <unordered_map>
#include <functional>

#include <interpreter.hpp>
#include <scenemanager.hpp>
#include <scenes.hpp>
#include <space.hpp>
#include <gameobject.hpp>
#include <component.hpp>
#include <exception.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace core
{
namespace scripting
{

static void help();
static std::optional<std::string> add_space(std::string name);
static std::optional<std::string> remove_space(std::string name);

static std::optional<std::string> add_space(std::string name)
{
  auto spm = we::scenes::impl::smanager->current_scene()->get_manager();
  auto sp = spm->add_space(name);
  // check if a valid space was returned
  if(!sp.use_count())
  {
    // invalid
    return {std::string("Error: Could not add space {" + name + "}")};
  }
  else return {};
}

static void help()
{
  throw UNIMPLEMENTED_EXCEPTION();
}

std::unordered_set<std::string> recognized_commands =
{
  "help",
  "add_space",
};

static std::unordered_map<std::string, std::any> cmd_map;

interpreter::interpreter()
{
  cmd_map["add_space"] = std::any(add_space);
}

interpreter::~interpreter()
{

}

std::optional<std::string> interpreter::parse(std::string line)
{
  throw UNIMPLEMENTED_EXCEPTION();
}

} // namespace scripting
} // namespace core
} // namespace waifuengine
