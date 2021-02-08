#include "scene_sandbox.hpp"
#include "scenemanager.hpp"
#include "texture.hpp"
#include "sprite.hpp"
#include "button.hpp"
#include "colors.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace scenes
  {

    std::shared_ptr<scene> build_sandbox_scene()
    {
      auto scn = scenes::blank_scene("Sandbox");
      auto sp_manager = scn->get_manager();
      sp_manager->build_default_spaces();
      // get default spaces
      auto bgsp = sp_manager->get_space("Background Space");
      auto chsp = sp_manager->get_space("Character Space");
      auto fxsp = sp_manager->get_space("FX Space");
      auto uisp = sp_manager->get_space("UI Space");
      auto trsp = sp_manager->get_space("Transition Space");
    
      auto test_button = uisp->add_object_t<ui::text_button>("test button", std::optional<fs::path>(), "Test Me");
      test_button->set_font("playtime.ttf");
      test_button->set_color(graphics::colors::color(255,255,255,255));
      return scn;
    }
  } // namespace scenes
}