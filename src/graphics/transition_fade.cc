
#include "transition_fade.hpp"
#include "gameobject.hpp"
#include "spacemanager.hpp"
#include "space.hpp"
#include "scenemanager.hpp"
#include "scenes.hpp"
#include "sprite.hpp"
#include "settings.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    namespace transitions
    {
      fade_in_ptr build_transition_fadein(int ms)
      {
        auto scn = we::scenes::current_scene();
        auto sp_manager = scn->get_manager();
        auto tr_sp = sp_manager->get_space("Transition Space");
        auto obj = tr_sp->add_object_t<fade_in>("fade_in_transition", ms);
        auto tr = dynamic_cast<fade_in *>(obj.get());
        tr->set_color({0.f, 0.f, 0.f, 1.0f});
        return obj;
      }

      fade_out_ptr build_transition_fadeout(int ms)
      {
        auto scn = we::scenes::current_scene();
        auto sp_manager = scn->get_manager();
        auto tr_sp = sp_manager->get_space("Transition Space");
        auto obj = tr_sp->add_object_t<fade_out>("fade_out_transition", ms);
        return obj;
      }

      fade_in::fade_in(std::string const &name, float ms) : primatives::sized_rectangle(name)
      {
        add_post_transition_script([]() -> void {});
        set_alpha(1.f);
        set_width(we::core::settings::read_t<int>("window_width"));
        set_height(we::core::settings::read_t<int>("window_height"));
        set_shader("rectangle_primative_shader");

        mg.start(name, ms, ms / 1000.0f, std::bind(&fade_in::subtract_alpha, this, 0.001f));
      }

      void fade_in::update(float dt)
      {
        if (!disabled_)
        {
          if (!mg.update(dt))
          {
            timeup();
          }

          std::scoped_lock lock(lock_);

          static auto const f = [&dt](std::pair<std::string, std::shared_ptr<::waifuengine::components::_impl::_base_component>> c) -> void { c.second->update(dt); };
          std::for_each(components_.begin(), components_.end(), f);
        }
      }

      void fade_in::subtract_alpha(float a)
      {
        set_alpha(get_alpha() - a);
      }

      void fade_in::timeup()
      {
        auto scn = we::scenes::current_scene();
        auto sp_manager = scn->get_manager();
        auto tr_sp = sp_manager->get_space("Transition Space");
        tr_sp->mark_object_for_removal(name_);
      }

      fade_in &fade_in::add_after(transition_list t)
      {
        queued_transitions.push_back(t);
        return *this;
      }

      fade_in& fade_in::add_post_transition_script(std::function<void()> s)
      {
        post_transition_script = s;
        return *this;
      }

      fade_out::fade_out(std::string const &name, int ms) : primatives::sized_rectangle(name)
      {
        set_alpha(0.f);

        set_width(we::core::settings::read_t<int>("window_width"));
        set_height(we::core::settings::read_t<int>("window_height"));
        set_shader("rectangle_primative_shader");
        mg.start(name, ms, ms / 1000.0f, std::bind(&fade_out::add_alpha, this, 0.001f));
      }

      void fade_out::timeup()
      {

      }

      void fade_out::update(float dt)
      {
        if (!disabled_)
        {
          if (!mg.update(dt))
          {
            timeup();
          }

          std::scoped_lock lock(lock_);

          static auto const f = [&dt](std::pair<std::string, std::shared_ptr<::waifuengine::components::_impl::_base_component>> c) -> void { c.second->update(dt); };
          std::for_each(components_.begin(), components_.end(), f);
        }
      }

      void fade_out::add_alpha(float a)
      {
        set_alpha(get_alpha() + a);
      }
    } // namespace transitions
  }   // namespace graphics
} // namespace waifuengine