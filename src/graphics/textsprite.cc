#include <textsprite.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace graphics
{
  textsprite::textsprite() : we::components::component<textsprite>() {}
  textsprite::~textsprite() {}

  void textsprite::text(std::string t)
  {
    ti.text(t);
  }

  std::string textsprite::text() const
  {
    return ti.text();
  }

  void textsprite::update(float) {}

  void textsprite::draw() const
  {
    ti.draw();
  }
}
} // namespace waifuengine