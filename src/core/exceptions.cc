/******************************************************************************/
/*!
\file   exceptions.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
  Exception classes

*/
/******************************************************************************/

#include <exceptions.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace core
{
namespace exceptions
{
  exception::exception() : std::exception(), message("Waifu Engine exception") {}
  exception::exception(const char * m) : ::std::exception(), message(m) {}
  exception::exception(std::string const& m) : ::std::exception(), message(m) {}
  exception::~exception() {}

  const char * exception::what() const throw() { return message.c_str(); }
  void exception::what(const char * m) { message = m; }
  void exception::what(std::string const& m) { message = m; }

  unimplemented::unimplemented() : exception("Unimplemented function") {} 
  unimplemented::unimplemented(const char * m) : exception(m) {}
  unimplemented::unimplemented(std::string const& m) : exception(m) {}
  unimplemented::~unimplemented() {}
}
} // namespace core
} // namespace waifuengine