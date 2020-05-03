#ifndef _we_scripting_hpp_
#define _we_scripting_hpp_

#include <optional>

#include <script_object.hpp>
#include <interpreter.hpp>

namespace waifuengine
{
  namespace core
  {
    namespace scripting
    {
      void init();
      void shutdown();

      // returns any sort of response or message from the command
      std::optional<std::string> interpret(std::string command);
    }
  }
}

#endif