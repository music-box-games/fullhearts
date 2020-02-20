#ifndef _WE_SDL_AUDIOMANAGER_HPP_
#define _WE_SDL_AUDIOMANAGER_HPP_

#include <string>
#include <unordered_map>
#include <memory>
#include <optional>

#include <SDL_mixer.h>

namespace waifuengine
{
  namespace audio
  {
    namespace sdl2
    {
      class sfx_handle
      {
      private:
        std::string name_;

        Mix_Chunk * data;

      public:
        sfx_handle(std::string name, std::string path);
        ~sfx_handle();

        void play();
      };

      using sfx_handle_ptr = std::shared_ptr<sfx_handle>;

      class music_handle
      {
      private:
        std::string name_;

        Mix_Music * data;

      public:
        music_handle(std::string name, std::string path);
        ~music_handle();

        void play();
      };

      using music_handle_ptr = std::shared_ptr<music_handle>;

      class audio_manager
      {
      private:
        using sfx_map = std::unordered_map<std::string, std::shared_ptr<sfx_handle>>;
        using music_map = std::unordered_map<std::string, std::shared_ptr<music_handle>>;

        sfx_map smap;
        music_map mmap;

      public:
        audio_manager();
        ~audio_manager();

        std::optional<sfx_handle_ptr> load_sfx(std::string name, std::string path);
        std::optional<music_handle_ptr> load_music(std::string name, std::string path);

        std::optional<sfx_handle_ptr> get_sfx(std::string name);
        std::optional<music_handle_ptr> get_music(std::string name);
      };
    }
  }
}

#endif 