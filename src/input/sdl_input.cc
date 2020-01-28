#include <sdl_input.hpp>

#ifdef WE_GRAPHICS_SDL2

#include <unordered_map>

#include <SDL.h>
#include <input_event.hpp>
#include <event_manager.hpp>
#include <engine.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace input
{
namespace sdl2
{

  static std::unordered_map<SDL_Keycode, we::input::keys> keymap = 
  {
    { SDLK_ESCAPE, we::input::keys::ESCAPE }, { SDLK_F1, we::input::keys::F1 }, { SDLK_F2, we::input::keys::F2 }, { SDLK_F3, we::input::keys::F3 },
    { SDLK_F4, we::input::keys::F4 }, {SDLK_F5, we::input::keys::F5 }, { SDLK_F6, we::input::keys::F6 }, { SDLK_F7, we::input::keys::F7 },
    { SDLK_F8, we::input::keys::F8 }, { SDLK_F9, we::input::keys::F9 }, { SDLK_F10, we::input::keys::F10 }, { SDLK_F11, we::input::keys::F11 }, { SDLK_F12, we::input::keys::F12 },
    { SDLK_1, we::input::keys::ONE }, { SDLK_2, we::input::keys::TWO }, { SDLK_3, we::input::keys::THREE }, { SDLK_4, we::input::keys::FOUR },
    { SDLK_5, we::input::keys::FIVE }, { SDLK_6, we::input::keys::SIX }, { SDLK_7, we::input::keys::SEVEN }, { SDLK_8, we::input::keys::EIGHT },
    { SDLK_9, we::input::keys::NINE }, { SDLK_0, we::input::keys::ZERO }, { SDLK_TAB, we::input::keys::TAB },
    { SDLK_q, we::input::keys::Q }, { SDLK_w, we::input::keys::W }, { SDLK_e, we::input::keys::E }, { SDLK_r, we::input::keys::R }, { SDLK_t, we::input::keys::T },
    { SDLK_y, we::input::keys::Y }, { SDLK_u, we::input::keys::U }, { SDLK_i, we::input::keys::I }, { SDLK_o, we::input::keys::O }, { SDLK_p, we::input::keys::P },
    { SDLK_LEFTBRACKET, we::input::keys::LBRACKET }, {SDLK_RIGHTBRACKET, we::input::keys::RBRACKET }, { SDLK_BACKSLASH, we::input::keys::BACKSLASH },
    { SDLK_CAPSLOCK, we::input::keys::CAPSLOCK }, { SDLK_a, we::input::keys::A }, { SDLK_s, we::input::keys::S }, { SDLK_d, we::input::keys::D },
    { SDLK_f, we::input::keys::F }, { SDLK_g, we::input::keys::G }, { SDLK_h, we::input::keys::H }, { SDLK_j, we::input::keys::J }, { SDLK_k, we::input::keys::K },
    { SDLK_l, we::input::keys::L }, { SDLK_SEMICOLON, we::input::keys::SEMICOLON }, { SDLK_QUOTE, we::input::keys::APOSTROPHE },  { SDLK_RETURN, we::input::keys::ENTER },
    { SDLK_LSHIFT, we::input::keys::LSHIFT }, { SDLK_z, we::input::keys::Z }, { SDLK_x, we::input::keys::X }, { SDLK_c, we::input::keys::C },
    { SDLK_v, we::input::keys::V }, { SDLK_b, we::input::keys::B }, { SDLK_n, we::input::keys::N }, { SDLK_m, we::input::keys::M }, {SDLK_COMMA, we::input::keys::COMMA },
    { SDLK_PERIOD, we::input::keys::PERIOD }, { SDLK_SLASH, we::input::keys::FORWARDSLASH }, { SDLK_RSHIFT, we::input::keys::RSHIFT },
    { SDLK_LCTRL, we::input::keys::LCTRL }, { SDLK_LALT, we::input::keys::LALT }, { SDLK_SPACE, we::input::keys::SPACE }, { SDLK_RALT, we::input::keys::RALT },
    { SDLK_RCTRL, we::input::keys::RCTRL },
  };

  void init()
  {

  }

  void update()
  {
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0)
    {
      if(e.type == SDL_QUIT)
      {
        we::core::engine::shutdown();
      }
      else if(e.type == SDL_KEYDOWN)
      {
        if(keymap.count(e.key.keysym.sym))
        {
          we::input::input_event ev;
          ev.key = keymap[e.key.keysym.sym];
          ev.type = we::input::input_type::PRESS;
          we::events::handle<input_event>(&ev);
        }
      }
    }
  }

  void shutdown()
  {

  }
}
}
}

#endif