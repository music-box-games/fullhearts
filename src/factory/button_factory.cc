#include <button_factory.hpp>
#include <scenemanager.hpp>
#include <sprite.hpp>
#include <textsprite.hpp>

namespace waifuengine
{
namespace factory
{
  std::shared_ptr<button> button_factory::build_imagebutton(std::string name, std::string file, std::shared_ptr<waifuengine::object_management::space> sp)
  {
    std::shared_ptr<waifuengine::object_management::space> s = (sp.use_count() != 0) ? sp : we::scenes::current_scene()->get_manager()->get_space("UI Space");
    auto obj = s->add_object(name);
    auto sprite = obj->add_component<we::graphics::sprite>();
    sprite->load_image(file);

    return obj;
  }

  std::shared_ptr<button> button_factory::build_textbutton(std::string name, std::string file, std::string text, std::shared_ptr<waifuengine::object_management::space> sp)
  {
    auto obj = build_imagebutton(name, file, sp);
    auto tsprite = obj->add_component<we::graphics::textsprite>();
    tsprite->text(text);

    return obj;
  }
}
} // namespace waifuengine
