#include <any>
#include <unordered_map>
#include <functional>
#include <string_view>
#include <boost/assign/list_of.hpp>

#include <interpreter.hpp>
#include <scenemanager.hpp>
#include <scenes.hpp>
#include <space.hpp>
#include <gameobject.hpp>
#include <component.hpp>
#include <exception.hpp>
#include <utils.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace core
{
namespace scripting
{
static std::optional<std::string> help();
static std::optional<std::string> add_space(std::string name);
static std::optional<std::string> remove_space(std::string name);

class cmd_map
{
public:
  std::optional<std::string> operator()(std::string s)
  {
    std::vector<std::string> tokens = utils::tokenize_string(s);
    switch(utils::string_to_int(tokens.at(0).c_str()))
    {
      case utils::string_to_int("add_space"):
        return add_space(tokens.at(1));
      case utils::string_to_int("help"):
        return help();
      default:
        return {};
    }
  }
};


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

static std::optional<std::string> help()
{
  throw UNIMPLEMENTED_EXCEPTION();
  return {};
}

interpreter::interpreter()
{

}

interpreter::~interpreter()
{

}

std::optional<std::string> interpreter::parse(std::string line)
{
  // tokenize
  return cmd_map()(line);
  
}

} // namespace scripting
} // namespace core
} // namespace waifuengine
