#include <string>

#include "exception.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
namespace core
{

_unimplemented_exception::_unimplemented_exception(const char * func)
{
  message = (std::string("Function {") + std::string(func) + std::string("} is unimplemented.")).c_str();
}

_unimplemented_exception::~_unimplemented_exception() {}

const char * _unimplemented_exception::what() const noexcept
{
  return message;
}

} // namespace core
} // namespace waifuengine