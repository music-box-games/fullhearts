#include <background_factory.hpp>
#include <spacemanager.hpp>
#include <space.hpp>
#include <scenemanager.hpp>
#include <sprite.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace factory
{
  std::shared_ptr<background> background_factory::build_background(std::string name, std::string file, std::shared_ptr<we::object_management::space> space)
  {
    std::shared_ptr<we::object_management::space> sp;
    if(space.use_count() == 0)
    {
      auto sc = we::scenes::current_scene();
      sp = sc->get_manager()->get_space("Background Space");
    }
    sp = space;
    auto obj = sp->add_object(name);
    std::shared_ptr<we::graphics::sprite> spr = obj->add_component<we::graphics::sprite>();
    spr->load_image(file);
    return obj;
  }
}
} // namespace waifuengine