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
#define ASSERT_USAGE(args, count) \
if(args.size() != count) \
{ \
  return { std::string("Usage: " + cmd_map.at(__func__).usage) }; \
}

namespace we = ::waifuengine;

namespace waifuengine
{
namespace core
{
namespace scripting
{
using argvec = std::vector<std::string>;
using script_func = std::function<std::optional<std::string>(std::vector<std::string>)>;
using script_ret = std::optional<std::string>;

#pragma region DebugMode

struct dbgfuncs
{
  script_func func;
  std::string usage;
};

static std::optional<std::string> help(argvec args);
static std::optional<std::string> add_space(argvec args);
static std::optional<std::string> remove_space(argvec args);
static std::optional<std::string> add_object(argvec args);
static std::optional<std::string> remove_object(argvec args);
static std::optional<std::string> add_component(argvec args);
static std::optional<std::string> remove_component(argvec args);

std::unordered_map<std::string, dbgfuncs> cmd_map =
{
  {"help", dbgfuncs{help, "help"}},
  {"add_space", dbgfuncs{add_space, "add_space <name>"}},
  {"remove_space", dbgfuncs{remove_space, "remove_space<name>"}},
  {"add_object", dbgfuncs{add_object, "add_object <space> <name>"}},
  {"remove_object", dbgfuncs{remove_object, "remove_object <space> <name>"}},
  {"add_component", dbgfuncs{add_component, "add_component <space> <object> <name>"}},
  {"remove_component", dbgfuncs{remove_component, "remove_component <space> <object> <name>"}},
};

#pragma region DbgScriptFunctions

static std::optional<std::string> add_component(argvec args)
{
  ASSERT_USAGE(args, 3);
  std::string space = args.at(0);
  std::string object = args.at(1);
  std::string name = args.at(2);

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

static std::optional<std::string> remove_component(argvec args)
{
  ASSERT_USAGE(args, 3);
  std::string space = args.at(0);
  std::string object = args.at(1);
  std::string name = args.at(2);

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

static std::optional<std::string> add_object(argvec args)
{
  ASSERT_USAGE(args, 2);
  std::string space = args.at(0);
  std::string name = args.at(1);

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

static std::optional<std::string> remove_object(argvec args)
{
  ASSERT_USAGE(args, 2);
  std::string space = args.at(0);
  std::string name = args.at(1);

  SPACE_MANAGER(spm);
  ASSERT_SPACE(spm, space);
  auto sp = spm->get_space(space);
  ASSERT_OBJECT(sp, space, name);
  sp->remove_object(name);
  return { std::string("Removed object \"" + name + "\" from space \"" + space + "\"") };
}

static std::optional<std::string> add_space(argvec args)
{
  ASSERT_USAGE(args, 1);
  std::string name = args.at(0);
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

static std::optional<std::string> remove_space(argvec args)
{
  ASSERT_USAGE(args, 1);
  std::string name = args.at(0);
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

static std::optional<std::string> help(argvec)
{
  std::stringstream ss;
  ss << "Recognized Commands:\n";
  
  std::for_each(cmd_map.begin(), cmd_map.end(), [&ss](auto pair) -> void {
    ss << "\t" << pair.first << "\n";
  });

  return {ss.str()};
}

#pragma endregion DbgScriptFunctions
#pragma endregion DebugMode

#pragma region ScriptMode

static script_ret background(argvec args)
{
  return {};
}

struct scptfunc
{
  script_func func;
  std::string usage;
};

std::unordered_map<std::string, scptfunc> scpt_cmd_map =
{
  {"background", scptfunc{background, "PUT USAGE HERE"}},
};

#pragma endregion ScriptMode

interpreter::interpreter(){}

interpreter::~interpreter(){}

std::optional<std::string> interpreter::parse(std::string line, interpreter_mode mode)
{
  if(line.empty())
  {
    return {};
  }
  // tokenize
  auto tokens = we::utils::tokenize_string(line);
  switch(mode)
  {
    case interpreter_mode::debug:
      {
        auto cmd = cmd_map.at(tokens.at(0));
        tokens.erase(tokens.begin());
        return cmd.func(tokens);
      }
    case interpreter_mode::script:
      {
        return {};
      }
    default:
      {
        return {};
      }
  }
}

} // namespace scripting
} // namespace core
} // namespace waifuengine
