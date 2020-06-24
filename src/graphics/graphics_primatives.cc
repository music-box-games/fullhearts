#include "graphics_primatives.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
  namespace graphics
  {
    namespace primatives
    {
      triangle::triangle(std::string name, std::array<glm::vec2, 3> verts) : base_primative(name), vertices(verts)
      {
        // attach default triangle shader
      }

      triangle::~triangle()
      {

      }

      void triangle::update(float)
      {

      }

      void triangle::draw() const
      {

      }
    }
  } // namespace graphics
} // namespace waifuengine