#include <button_factory.hpp>
#include <scenemanager.hpp>
#include <sprite.hpp>
#include <textsprite.hpp>
#include <transform.hpp>
#include <window.hpp>
#include <graphics.hpp>
#include <button_collider.hpp>

namespace waifuengine
{
namespace factory
{
  std::shared_ptr<button> button_factory::build_imagebutton(std::string name, std::string imname, std::string hover_name, std::function<void()> f, std::shared_ptr<waifuengine::object_management::space> sp)
  {
    std::shared_ptr<waifuengine::object_management::space> s = (sp.use_count() != 0) ? sp : we::scenes::current_scene()->get_manager()->get_space("UI Space");
    auto obj = s->add_object(name);
    auto sprite = obj->add_component<we::graphics::sprite>();
    sprite->link_image(imname);
    auto tr = obj->add_component<we::physics::transform>();
    // TODO: temp
    auto w = waifuengine::graphics::get_window();
    SDL_Rect r;
    r.x = w->width() * 0.5f; 
    r.y = w->height() * 0.65f;
    r.w = w->width() * 0.1f;
    r.h = w->height() * 0.2f;
    tr->set(r);

    auto col = obj->add_component<we::physics::button_collider>();
    col->set_trigger(f);

    col->set_nonhover_image(imname);
    col->set_hover_image(hover_name);

    return obj;
  }

  std::shared_ptr<button> button_factory::build_textbutton(std::string name, std::string imname, std::string hover_name, std::string text, std::function<void()> f, std::shared_ptr<waifuengine::object_management::space> sp)
  {
    auto obj = build_imagebutton(name, imname, hover_name, f, sp);
    auto tsprite = obj->add_component<we::graphics::textsprite>();
    tsprite->text(text);

    return obj;
  }
}
} // namespace waifuengine
