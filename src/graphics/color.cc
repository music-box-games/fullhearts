#include <unordered_map>

#include <color.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    #ifdef WE_GRAPHICS_SDL2
    namespace sdl2
    {
      std::unordered_map<colors, SDL_Color> bank =
      {
        {colors::red, {0xFF, 0x0, 0x0, 0xFF}},
        {colors::green, {0x0, 0xFF, 0x0, 0xFF}},
        {colors::blue, {0x0, 0x0, 0xFF, 0xFF}},
        {colors::black, {0x0, 0x0, 0x0, 0xFF}},
      };

      SDL_Color convert(colors c)
      {
        return (bank.count(c)) ? bank[c] : SDL_Color{0,0,0};
      }
    }
    #endif // WE_GRAPHICS_SDL2

    static std::unordered_map<colors, color_vals> color_bank = 
    {
      {colors::red, {0xFF, 0x0, 0x0, 0xFF}},
      {colors::green, {0x0, 0xFF, 0x0, 0xFF}},
      {colors::blue, {0x0, 0x0, 0xFF, 0xFF}},
      {colors::black, {0x0, 0x0, 0x0, 0xFF}},
    };

    color_vals get_color(colors c)
    {
      return (color_bank.count(c)) ? color_bank[c] : color_vals{};
    }

    color_type convert_color(colors c)
    {
      #ifdef WE_GRAPHICS_SDL2
      return sdl2::convert(c);
      #endif
    }
  }
}