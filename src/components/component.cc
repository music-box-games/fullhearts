#include <component.hpp>
#include <physics.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace components
{
namespace _impl
{

std::unordered_map<component_types, std::type_index> component_index = 
{
  {component_types::physics2, typeid(we::components::physics)},
}

}
} // namespace components
} // namespace waifuengine