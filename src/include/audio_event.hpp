#ifndef _WE_AUDIO_EVENT_HPP_
#define _WE_AUDIO_EVENT_HPP_

#include <string>

namespace waifuengine
{
  namespace audio
  {
    class audio_event
    {
    public:
      enum class action
      {
        play,
        pause,
        stop,

        // special
        d,
      };

      audio_event();
      audio_event(action a, std::string n);
      ~audio_event();

      action a;
      std::string name;
    };
  }
}

#endif