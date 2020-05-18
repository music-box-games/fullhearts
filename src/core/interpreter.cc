#include <any>
#include <unordered_map>
#include <functional>
#include <string_view>
#include <sstream>

#include <boost/assign/list_of.hpp>

#include <interpreter.hpp>
#include <scenemanager.hpp>
#include <scenes.hpp>
#include <space.hpp>
#include <gameobject.hpp>
#include <component.hpp>
#include <exception.hpp>
#include <utils.hpp>
#include <component.hpp>
#include <dummy.hpp>

#define SPACE_MANAGER(x) auto x = we::scenes::impl::smanager->current_scene()->get_manager()

#define ASSERT_SPACE(spm, name) if(!spm->has_space(name)) { return { std::string("No space\"" + space + "\" found") };}
#define ASSERT_OBJECT(space, space_name, name) if(!space->has(name)) { return { std::string("No object \"" + name + "\" found in space \"" + space_name + "\"") };}
#define ASSERT_ARG_COUNT(args, count) if(args.size() != count) { return { std::string("Improper usage") };}

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
static std::optional<std::string> add_object(std::string space, std::string name);
static std::optional<std::string> remove_object(std::string space, std::string name);
static std::optional<std::string> add_component(std::string space, std::string object, std::string name);
static std::optional<std::string> remove_component(std::string space, std::string object, std::string name);

static std::optional<std::string> add_component(std::string space, std::string object, std::string name)
{
  static const std::unordered_map<std::string, std::function<void(std::shared_ptr<we::object_management::gameobject>, std::string)>> add_comps =
  {
    {we::components::dummy::NAME, [](std::shared_ptr<we::object_management::gameobject> g, std::string comp_name) -> void
    {
      g->add_component<we::components::dummy>();
    }
    },
  };

  SPACE_MANAGER(spm);
  ASSERT_SPACE(spm, space);
  auto sp = spm->get_space(space);
  ASSERT_OBJECT(sp, space, object);
  auto obj = sp->get_object(object);
  add_comps.at(name)(obj, name);

  if(obj->has_component(name))
  {
    return { std::string("Added \"" + name + "\" to \"" + object + "\"") };
  }
  else
  {
    return { std::string("Could not add \"" + name + "\" to \"" + object + "\"") };
  }
}

static std::optional<std::string> remove_component(std::string space, std::string object, std::string name)
{
  static const std::unordered_map<std::string, std::function<void(std::shared_ptr<we::object_management::gameobject>, std::string)>> remove_comps =
  {
    {we::components::dummy::NAME, [](std::shared_ptr<we::object_management::gameobject> g, std::string comp_name) -> void
    {
      g->remove_component<we::components::dummy>();
    }
    },
  };

  SPACE_MANAGER(spm);
  ASSERT_SPACE(spm, space);
  auto sp = spm->get_space(space);
  ASSERT_OBJECT(sp, space, object);
  auto obj = sp->get_object(object);
  remove_comps.at(name)(obj, name);
  if(obj->has_component(name))
  {
    return { std::string("Could not remove \"" + name + "\" from \"" + object + "\"") };
  }
  else
  {
    return { std::string("Removed \"" + name + "\" from \"" + object + "\"") };
  }
}

static std::optional<std::string> add_object(std::string space, std::string name)
{
  SPACE_MANAGER(spm);
  ASSERT_SPACE(spm, space);
  auto sp = spm->get_space(space);
  auto obj = sp->add_object(name);
  if(!obj.use_count())
  {
    return {std::string("Could not add object \"" + name + "\" to \"" + space + "\"") };
  }
  else
  {
    return {std::string("Added \"" + name + "\" to \"" + space + "\"") };
  }
}

static std::optional<std::string> remove_object(std::string space, std::string name)
{
  SPACE_MANAGER(spm);
  ASSERT_SPACE(spm, space);
  auto sp = spm->get_space(space);
  ASSERT_OBJECT(sp, space, name);
  sp->remove_object(name);
  return { std::string("Removed object \"" + name + "\" from space \"" + space + "\"") };
}

static std::optional<std::string> add_space(std::string name)
{
  auto spm = we::scenes::impl::smanager->current_scene()->get_manager();
  auto sp = spm->add_space(name);
  // check if a valid space was returned
  if(!sp.use_count())
  {
    // invalid
    return {std::string("Error: Could not add space \"" + name + "\"")};
  }
  else
  {
    return {std::string("Added Space: \"" + name + "\"")};
  }
}

static std::optional<std::string> remove_space(std::string name)
{
  auto spm = we::scenes::impl::smanager->current_scene()->get_manager();
  if(spm->has_space(name))
  {
    spm->remove_space(name);
    return { std::string("Removed Space: \"" + name + "\"")};
  }
  else
  {
    return { std::string("No space named: \"" + name + "\"")};
  }
}

static std::optional<std::string> help()
{
  std::stringstream ss;
  ss << "Recognized Commands:\n";
  ss << "\tadd_space\n";
  ss << "\tremove_space\n";
  ss << "\tadd_object\n";
  ss << "\tremove_object\n";
  ss << "\tadd_component\n";
  ss << "\tremove_component\n";

  ss << "\thelp\n";

  return {ss.str()};
}

class cmd_map
{
public:
  std::optional<std::string> operator()(std::string s)
  {
    std::vector<std::string> tokens = utils::tokenize_string(s);
    switch(utils::string_to_int(tokens.at(0).c_str()))
    {
      case utils::string_to_int("add_space"):
        ASSERT_ARG_COUNT(tokens, 2);
        return add_space(tokens.at(1));
      case utils::string_to_int("remove_space"):
        ASSERT_ARG_COUNT(tokens, 2);
        return remove_space(tokens.at(1));
      case utils::string_to_int("help"):
        return help();
      case utils::string_to_int("add_object"):
        ASSERT_ARG_COUNT(tokens, 3);
        return add_object(tokens.at(1), tokens.at(2));
      case utils::string_to_int("remove_object"):
        ASSERT_ARG_COUNT(tokens, 3);
        return remove_object(tokens.at(1), tokens.at(2));
      case utils::string_to_int("add_component"):
        ASSERT_ARG_COUNT(tokens, 4);
        return add_component(tokens.at(1), tokens.at(2), tokens.at(3));
      case utils::string_to_int("remove_component"):
        ASSERT_ARG_COUNT(tokens, 4);
        return remove_component(tokens.at(1), tokens.at(2), tokens.at(3));
      default:
        return { std::string("Unknown Command: " + tokens[0]) };
    }
  }
};

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
