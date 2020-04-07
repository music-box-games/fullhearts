#ifndef _WE_FMODLL_AUDIOMANAGER_HPP_
#define _WE_FMODLL_AUDIOMANAGER_HPP_

#ifdef WE_AUDIO_FMOD_LL

namespace waifuengine
{
  namespace audio
  {
    namespace fmodll_impl
    {
      class audio_manager
      {
      public:
        audio_manager();
        ~audio_manager();

        void update();

      private:
      };
    }
  }
}

#endif
#endif