#include <memory>

#include <audio.hpp>

#ifdef WE_AUDIO_SDL2
#include <sdl_audio.hpp>
#endif
#include <audiomanager.hpp>

namespace waifuengine
{
namespace audio
{
  static std::shared_ptr<audio_manager> man;

  void init()
  {
    man = std::shared_ptr<audio_manager>(new audio_manager());
  }

  void update()
  {
    
  }

  void shutdown()
  {
    man.reset();
  }
}
} // namespace waifuengine
