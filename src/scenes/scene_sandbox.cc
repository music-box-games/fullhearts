#include "scene_sandbox.hpp"
#include "scenemanager.hpp"
#include "input_listener.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace scenes
  {
    std::string triangle0_name = "test_triangle0";
    std::string triangle1_name = "test_triangle1";
    std::string shader0_name = "testshader0";
    std::string shader1_name = "testshader1";

    static void enable_only(std::string name)
    {
      auto scn = we::scenes::current_scene();
      auto *sc_manager = scn->get_manager();
      auto sp = sc_manager->get_space("test_space");
      sp->disable_all();
      sp->get_object(name)->disable(false);
    }

    std::shared_ptr<scene> build_sandbox_scene()
    {
      auto scn = blank_scene("test");
      auto *sc_manager = scn->get_manager();
      auto sp = sc_manager->add_space("test_space");
      auto i_listener = dynamic_cast<we::utils::input_listener *>(sp->add_object_t<we::utils::input_listener>("input_listener").get());
      std::function<void(we::utils::input_listener::event_receive_type *)> f = [&](we::utils::input_listener::event_receive_type * e) -> void 
      {
        we::utils::input_listener::event_subscribe_type * ie = dynamic_cast<we::utils::input_listener::event_subscribe_type *>(e);
        if(ie->a == we::graphics::input::action::press)
        {
          switch(ie->k)
          {
          case we::graphics::input::key::zero:
            enable_only(triangle0_name);
            break;
          case we::graphics::input::key::one:
            enable_only(triangle1_name);
            break;
          }
        }
      };
      i_listener->set_handler(f);

      auto obj0 = sp->add_object_t<we::graphics::shaders::test::test_triangle0>(triangle0_name);
      float verts0[] = {
          -0.5f, -0.5f, 0.0f,
          0.5f, -0.5f, 0.0f,
          0.0f, 0.5f, 0.0f};
      (dynamic_cast<we::graphics::primatives::triangle *>((obj0.get())))->set_vertices(verts0, 9);
      (dynamic_cast<we::graphics::primatives::triangle *>((obj0.get())))->set_shader(shader0_name);

      auto obj1 = sp->add_object_t<we::graphics::shaders::test::test_triangle1>(triangle1_name);
      float verts1[] = {
          // positions         // colors
          0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // bottom right
         -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // bottom left
          0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // top
          };
      (dynamic_cast<we::graphics::primatives::triangle *>((obj1.get())))->set_vertices(verts1, 18);
      (dynamic_cast<we::graphics::primatives::triangle *>((obj1.get())))->set_shader(shader1_name);
      
      sp->disable_all();
      obj1->disable(false);

      return scn;
    }
  } // namespace scenes
}