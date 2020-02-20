#include <audio_event.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace audio
{
  audio_event::audio_event() : a(action::d), name("") {}
  audio_event::audio_event(action ac, std::string n) : a(ac), name(n) {}
  audio_event::~audio_event() {}
}
} // namespace waifuengine
