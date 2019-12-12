#include <dummy.hpp>

namespace waifuengine
{
  namespace components
  {
    dummy::dummy() : component<dummy>() {}
    dummy::~dummy() {}

    void dummy::update(float) {}
    void dummy::draw() const {}
  }
}
