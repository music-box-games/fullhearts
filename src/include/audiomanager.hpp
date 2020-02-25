#ifndef _WE_AUDIOMANAGER_HPP_
#define _WE_AUDIOMANAGER_HPP_

#ifdef WE_AUDIO_SDL2

#include <sdl_audiomanager.hpp>

namespace waifuengine
{
  namespace audio
  {
    typedef sdl2::audio_manager audio_manager;
  }
}

#endif
#endif