#include <input.hpp>

namespace waifuengine
{
namespace graphics
{
namespace input
{

namespace impl
{

std::unordered_map<decltype(GLFW_KEY_UNKNOWN), key> keyset = 
{
  {GLFW_KEY_UNKNOWN, key::default},
  {GLFW_KEY_SPACE, key::space},
  {GLFW_KEY_APOSTROPHE, key::apostrophe},
  {GLFW_KEY_COMMA, key::comma},
  {GLFW_KEY_MINUS, key::minus},
  {GLFW_KEY_PERIOD, key::period},
  {GLFW_KEY_SLASH, key::slash},
  {GLFW_KEY_0, key::zero}, {GLFW_KEY_1, key::one}, {GLFW_KEY_2, key::two}, {GLFW_KEY_3, key::three}, {GLFW_KEY_4, key::four}, {GLFW_KEY_5, key::five},
  {GLFW_KEY_6, key::six}, {GLFW_KEY_7, key::seven}, {GLFW_KEY_8, key::eight}, {GLFW_KEY_9, key::nine},
  {GLFW_KEY_SEMICOLON, key::semicolon}, {GLFW_KEY_EQUAL, key::equal},
  {GLFW_KEY_A, key::a}, {GLFW_KEY_B, key::b}, {GLFW_KEY_C, key::c}, {GLFW_KEY_D, key::d}, {GLFW_KEY_E, key::e}, {GLFW_KEY_F, key::f}, {GLFW_KEY_G, key::g},
  {GLFW_KEY_H, key::h}, {GLFW_KEY_I, key::i}, {GLFW_KEY_J, key::j}, {GLFW_KEY_K, key::k}, {GLFW_KEY_L, key::l}, {GLFW_KEY_M, key::m}, {GLFW_KEY_N, key::n},
  {GLFW_KEY_O, key::o}, {GLFW_KEY_P, key::p}, {GLFW_KEY_Q, key::q}, {GLFW_KEY_R, key::r}, {GLFW_KEY_S, key::s}, {GLFW_KEY_T, key::t}, {GLFW_KEY_U, key::u},
  {GLFW_KEY_V, key::v}, {GLFW_KEY_W, key::w}, {GLFW_KEY_X, key::x}, {GLFW_KEY_Y, key::y}, {GLFW_KEY_Z, key::z},
  {GLFW_KEY_LEFT_BRACKET, key::left_bracket}, {GLFW_KEY_BACKSLASH, key::backslash}, {GLFW_KEY_RIGHT_BRACKET, key::right_bracket},
  {GLFW_KEY_GRAVE_ACCENT, key::grave_accent}, {GLFW_KEY_WORLD_1, key::world_1}, {GLFW_KEY_WORLD_2, key::world_2}, {GLFW_KEY_ESCAPE, key::escape},
  {GLFW_KEY_ENTER, key::enter}, {GLFW_KEY_TAB, key::tab}, {GLFW_KEY_BACKSPACE, key::backspace}, {GLFW_KEY_INSERT, key::insert}, {GLFW_KEY_DELETE, key::del},
  {GLFW_KEY_RIGHT, key::right}, {GLFW_KEY_LEFT, key::left}, {GLFW_KEY_DOWN, key::down}, {GLFW_KEY_UP, key::up}, {GLFW_KEY_PAGE_UP, key::page_up},
  {GLFW_KEY_PAGE_DOWN, key::page_down}, {GLFW_KEY_HOME, key::home}, {GLFW_KEY_END, key::end}, {GLFW_KEY_CAPS_LOCK, key::caps_lock}, {GLFW_KEY_SCROLL_LOCK, key::scroll_lock},
  {GLFW_KEY_NUM_LOCK, key::num_lock}, {GLFW_KEY_PRINT_SCREEN, key::print_screen}, {GLFW_KEY_PAUSE, key::pause}, {GLFW_KEY_F2, key::f2}, {GLFW_KEY_F3, key::f3},
  {GLFW_KEY_F4, key::f4}, {GLFW_KEY_F5, key::f5}, {GLFW_KEY_F6, key::f6}, {GLFW_KEY_F7, key::f7}, {GLFW_KEY_F8, key::f8}, {GLFW_KEY_F9, key::f9}, {GLFW_KEY_F10, key::f10},
  {GLFW_KEY_F11, key::f11}, {GLFW_KEY_F12, key::f12}, {GLFW_KEY_F13, key::f13}, {GLFW_KEY_F14, key::f14}, {GLFW_KEY_F15, key::f15}, {GLFW_KEY_F16, key::f16}, {GLFW_KEY_F17, key::f17}, 
  {GLFW_KEY_F18, key::f18}, {GLFW_KEY_F19, key::f19}, {GLFW_KEY_F20, key::f20}, {GLFW_KEY_F21, key::f21}, {GLFW_KEY_F22, key::f22}, {GLFW_KEY_F23, key::f23},
  {GLFW_KEY_F24, key::f24}, {GLFW_KEY_F25, key::f25}, {GLFW_KEY_KP_0, key::kp_0}, {GLFW_KEY_KP_1, key::kp_1}, {GLFW_KEY_KP_2, key::kp_2}, {GLFW_KEY_KP_3, key::kp_3},
  {GLFW_KEY_KP_4, key::kp_4}, {GLFW_KEY_KP_5, key::kp_5}, {GLFW_KEY_KP_6, key::kp_6}, {GLFW_KEY_KP_7, key::kp_7}, {GLFW_KEY_KP_8, key::kp_8}, {GLFW_KEY_KP_9, key::kp_9},
  {GLFW_KEY_KP_DECIMAL, key::kp_decimal}, {GLFW_KEY_KP_DIVIDE, key::kp_divide}, {GLFW_KEY_KP_MULTIPLY, key::kp_multiply}, {GLFW_KEY_KP_SUBTRACT, key::kp_subtract},
  {GLFW_KEY_KP_ADD, key::kp_add}, {GLFW_KEY_KP_ENTER, key::kp_enter}, {GLFW_KEY_KP_EQUAL, key::kp_equal}, {GLFW_KEY_LEFT_SHIFT, key::left_shift},
  {GLFW_KEY_LEFT_CONTROL, key::left_control}, {GLFW_KEY_LEFT_ALT, key::left_alt}, {GLFW_KEY_LEFT_SUPER, key::left_super}, {GLFW_KEY_RIGHT_SHIFT, key::right_shift},
  {GLFW_KEY_RIGHT_CONTROL, key::right_control}, {GLFW_KEY_RIGHT_ALT, key::right_alt}, {GLFW_KEY_RIGHT_SUPER, key::right_super}, {GLFW_KEY_MENU, key::menu},
};

std::unordered_map<decltype(GLFW_PRESS), action> actionset =
{
  {GLFW_PRESS, action::press},
  {GLFW_RELEASE, action::release},
};

} // namespace impl

input_event::input_event() : event(std::string(NAME)), k(key::default), a(action::default), w(window_id_type{}) {}
input_event::input_event(key k, action a, window_id_type w) : event(std::string(NAME)), k(k), a(a), w(w) {}
input_event::~input_event() {}

void process()
{
  window::process_all_input();
}

} // namespace input
} // namespace graphics
} // namespace waifuengine