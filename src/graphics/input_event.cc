#include <unordered_map>

#include "input_event.hpp"

namespace waifuengine
{
  namespace graphics
  {
    namespace input
    {
      using sfks = sf::Keyboard::Key;
      std::unordered_map<sfks, keys> keymap =
      {
        {sfks::Unknown, keys::unknown},
        {sfks::Escape, keys::esc}, {sfks::F1, keys::f1}, {sfks::F2, keys::f2}, {sfks::F3, keys::f3},
        {sfks::F4, keys::f4}, {sfks::F5, keys::f5}, {sfks::F6, keys::f6}, {sfks::F7, keys::f7},
        {sfks::F8, keys::f8}, {sfks::F9, keys::f9}, {sfks::F10, keys::f10}, {sfks::F11, keys::f11}, {sfks::F12, keys::f12},
        {sfks::Delete, keys::del}, {sfks::Tilde, keys::backtick}, {sfks::Num1, keys::one}, {sfks::Num2, keys::two},
        {sfks::Num3, keys::three}, {sfks::Num4, keys::four}, {sfks::Num5, keys::five}, {sfks::Num6, keys::six},
        {sfks::Num7, keys::seven}, {sfks::Num8, keys::eight}, {sfks::Num9, keys::nine}, {sfks::Num0, keys::zero},
        {sfks::Dash, keys::minus}, {sfks::Equal, keys::equals}, {sfks::BackSpack, keys::backspace},
        {sfks::Tab, keys::tab}, {sfks::Q, keys::q}, {sfks::W, keys::w}, {sfks::E, keys::e}, {sfks::R, keys::R},
        {sfks::T, keys::t}, {sfks::Y, keys::y}, {sfks::U, keys::u}, {sfks::I, keys::i}, {sfks::O, keys::o},
        {sfks::P, keys::p}, {sfks::LBracket, keys::bracket_open}, {sfks::RBracket, keys::bracket_close},
        {sfks::BackSlash, keys::backslash}, {sfks::A, keys::a}, {sfks::S, keys::s}, {sfks::D, keys::d},
        {sfks::F, keys::f}, {sfks::G, keys::g}, {sfks::H, keys::h}, {sfks::J, keys::j}, {sfks::K, keys::k},
        {sfks::L, keys::l}, {sfks::Semicolon, keys::semicolon}, {sfks::Quote, keys::single_quote}, {sfks::Enter, keys::enter},
        {sfks::LShift, keys::lshift}, {sfks::Z, keys::z}, {sfks::X, keys::x}, {sfks::C, keys::c}, {sfks::V, keys::v},
        {sfks::B, keys::b}, {sfks::N, keys::n}, {sfks::M, keys::m}, {sfks::Comma, keys::comma}, {sfks::Period, keys::period},
        {sfks::Slash, keys::forwardslash}, {sfks::RShift, keys::rshift}, {sfks::LControl, keys::lctrl},
        {sfks::LAlt, keys::lalt}, {sfks::Space, keys::space}, {sfks::RAlt, keys::ralt}, {sfks::RCtrl, keys::rctrl},
        {sfks::Numpad1, keys::num_one}, {sfks::Numpad2, keys::num_two}, {sfks::Numpad3, keys::num_three}, {sfks::Numpad4, keys::num_four},
        {sfks::Numpad5, keys::num_five}, {sfks::Numpad6, keys::num_six}, {sfks::Numpad7, keys::num_seven},
        {sfks::Numpad8, keys::num_eigth}, {sfks::Numpad9, keys:::num_nine}, {sfks::Numpad0, keys::num_zero},
        {sfks::Add, keys::num_plus}, {sfks::Subtract, keys::minus}, {sfks::Multiply, keys::num_multiply}, {sfks::Divide, keys::num_divide},
      };

      keys from_api_key(sfks k)
      {
        if(keymap.count(k))
        {
          return keymap.at(k);
        }
        else
        { 
          return keys::unknown;
        } 
      }

      input_event::input_event(keys k, actions a) : key(k), action(a) {}
      input_event::~input_event() {}
    }
  }
}