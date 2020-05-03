#include <memory>

#include <scripting.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace core
{
namespace scripting
{
namespace impl
{
  std::shared_ptr<we::core::scripting::interpreter> interp;
}

void init()
{
  if(impl::interp.use_count())
  {
    impl::interp.reset();
  }
  impl::interp = std::shared_ptr<we::core::scripting::interpreter>(new we::core::scripting::interpreter());
}

void shutdown()
{
  impl::interp.reset();
}

std::optional<std::string> interpret(std::string command)
{
  return impl::interp->parse(command);
}

} // namespace scripting
} // namespace core
} // namespace waifuengine