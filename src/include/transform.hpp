#ifndef _WE_TRANSFORM_HPP_
#define _WE_TRANSFORM_HPP_

#include <glm/glm.hpp>
#include "debug.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class transform
    {
    private:
      friend class waifuengine::core::debug::imgui_listener;
      glm::mat4 trans;
      bool dirty;

      glm::vec2 scale_;
      glm::vec2 pos_;

      float rot_deg;

    public:
      transform();
      ~transform();

      void update(float dt);
      void draw() const;
      
      void reset();
      void rotate(float degrees);
      void translate(glm::vec2 distance);
      void uniform_scale(float s);
      void scale(glm::vec2 s);

      void lock_screen_proportion(bool set = true);
      glm::mat4 * data();
    };
  }
}

#endif