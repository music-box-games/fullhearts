#include <sdl_audiomanager.hpp>

namespace waifuengine
{
namespace audio
{
namespace sdl2
{
  sfx_handle::sfx_handle(std::string name, std::string path) : name_(name), data(nullptr)
  {
    data = Mix_LoadWAV(path);
    if(!data)
    {
      // error message
      // TODO: decide on whether to show dialog or throw and show dialog when caught
    }
  }

  sfx_handle::~sfx_handle()
  {
    Mix_FreeChunk(data);
  }

  void sfx_handle::play()
  {

  }

  music_handle::music_handle(std::string name, std::string path) : name_(name), data(nullptr)
  {
    data = Mix_LoadMUS(path);
    if(!data)
    {
      // error
    }
  }

  music_handle::~music_handle()
  {
    Mix_FreeMusic(data);
  }

  music_handle::play()
  {

  }

  audio_manager::audio_manager() {}
  audio_manager::~audio_manager() {}

  std::optional<sfx_handle_ptr> audio_manager::load_sfx(std::string name, std::string path)
  {
    auto * sfx = new sfx_handle(name, path);
    if(sfx)
    {
      auto res = smap.insert_or_assign(name, sfx_handle_ptr(sfx));
      if(res.second)
      {
        return *(res.first);
      }
    }
    return {};
  }

  std::optional<music_handle_ptr> audio_manager::load_music(std::string name, std::string path)
  {
    auto * mus = new music_handle(name, path);
    if(mus)
    {
      auto res = mmap.insert_or_assign(name, music_handle_ptr(mus));
      if(res.second)
      {
        return *(res.first);
      }
    }
    return {};
  }

  std::optional<sfx_handle_ptr> audio_manager::get_sfx(std::string name)
  {
    if(smap.count(name))
    {
      return smap[name];
    }
    else return {};
  }

  std::optional<music_handle_ptr> audio_manager::get_music(std::string name)
  {
    if(mmap.count(name))
    {
      return mmap[name];
    }
    else return {};
  }
}
} // namespace audio
} // namespace waifuengine