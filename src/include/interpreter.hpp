#ifndef _we_script_parser_hpp_
#define _we_script_parser_hpp_

#include <string>
#include <unordered_set>
#include <optional>

namespace waifuengine
{
  namespace core
  {
    namespace scripting
    {
      enum class interpreter_mode
      {
        debug,
        script,
      };

      extern std::unordered_set<std::string> recognized_commands;

      class interpreter
      {
      public:
        interpreter();
        ~interpreter();

        std::optional<std::string> parse(std::string line, interpreter_mode mode = interpreter_mode::script);
      private:
      };
    }
  }
}

#endif