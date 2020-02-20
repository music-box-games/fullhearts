#include <sdl_audio.hpp>

#include <SDL_mixer.h>

namespace waifuengine
{
namespace audio
{
namespace sdl2
{
  void init()
  {
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
      // error handle
    }
  }

  void update()
  {

  }

  void shutdown()
  {
    Mix_Quit();
  }
}
} // namespace audio
} // namespace waifuengine