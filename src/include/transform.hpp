#ifndef _WE_TRANSFORM_HPP_
#define _WE_TRANSFORM_HPP_

#include <array>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

#include "debug.hpp"
#include "component.hpp"

namespace waifuengine
{
  namespace graphics
  {
    struct decomposed_transform
    {
      glm::vec3 scale;
      glm::quat rotation;
      glm::vec3 translation;
      glm::vec3 skew;
      glm::vec4 perspective;
    };

    class rect_dimensions
    {
    public:
      glm::vec2 center;
      glm::vec2 dimensions;

      std::array<glm::vec2, 4> vertices; // top-left, top-right, bottom-right, bottom-left

      rect_dimensions(glm::vec2 c, glm::vec2 d);
    };

    class transform : public components::component<transform>
    {
    private:
      friend class boost::serialization::access;
      friend class waifuengine::core::debug::imgui_listener;
      glm::mat4 trans;
      bool dirty;

      glm::vec2 scale_;
      glm::vec2 pos_;

      float rot_deg;

      template<class Archive>
      void serialize(Archive& a, unsigned int const v)
      {
        a & boost::serialization::base_object<comonents::component<transform>(this);
        
      }

    public:
      COMPONENT_NAME(transform);
      COMPONENT_TYPE(transform);
      enum class axis
      {
        x,
        y,
        z,
      };
      static float convert_pixels_to_screen_coords(float p, axis a);

      transform();
      virtual ~transform();

      virtual void update(float dt);
      virtual void draw() const;

      void reset();
      void rotate(float degrees);
      float rotate() const;
      void translate(glm::vec2 distance);
      glm::vec2 translate() const;
      void uniform_scale(float s);
      void scale(glm::vec2 s);
      glm::vec2 scale() const;

      void lock_screen_proportion(bool set = true);
      glm::mat4 *data();

      decomposed_transform decompose() const;
    };
  } // namespace graphics
} // namespace waifuengine

#endif