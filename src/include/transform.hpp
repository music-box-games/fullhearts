#ifndef _WE_TRANSFORM_HPP_
#define _WE_TRANSFORM_HPP_

#include <array>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

#include "debug.hpp"
#include "component.hpp"
#include "coordinates.hpp"
#include "point2d.hpp"

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
      screen_point2d pos_;

      float rot_deg;

      float width_ratio;
      float height_ratio;

      template<class Archive>
      void serialize(Archive& a, unsigned int const v)
      {
        a & boost::serialization::base_object<comonents::component<transform>(this);
        
      }

      void calculate_transform();

    public:
      COMPONENT_REGISTER(transform);
      
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
      void set_rotation(float degrees);
      float rotate() const;
      void translate(glm::vec2 distance);
      void set_translation(glm::vec2 position);
      glm::vec2 translate() const;
      void uniform_scale(float s);
      void scale(glm::vec2 s);
      void set_scale(glm::vec2 s);
      glm::vec2 scale() const;

      int width_in_pixels() const;
      int height_in_pixels() const;
      glm::vec2 dimensions_in_pixels() const;
      [[deprecated]] glm::vec2 position_in_pixels() const;

      /**
        * @brief Gets the screen coordinates for the center of the object
        * @return Object's screen coordinates.
      */
      screen_point2d get_position_in_screen_coordinates() const;

      /**
        * @brief Gets the world coordinates for the center of the object
        * @return Object's world coordinates.
      */
      world_point2d get_position_in_world_coordinates() const;

      /**
        * @brief Sets the center of the object to the position given in screen coordinates.
        * @param p Point in screen coordinates to set position to.
      */
      void set_position_in_screen_coordinates(screen_point2d p);

      /**
        * @brief Sets the center of the object to the position given in world coordinates.
        * @param p Point in world coordinates to set position to.
      */
     void set_position_in_world_coordinates(world_point2d p);

     /**
       * @brief Sets the "width" of the object.
       * 
       * The width ratio is a ratio of the width of the object to the width of the window.
       * 
       * @param wr Ratio of object width to window width.
     */
     void set_width_ratio(float wr);

      /**
        * @brief Sets the "height" of the object.
        * 
        * The height ratio is a ratio of the height of the object to the height of the window.
        * 
        * @param wh Ratio of object height to window height.
      */
      void set_height_ratio(float wh);

      /**
        * @brief Gets the width ratio of the object.
        * @return The object's width ratio.
      */
      float get_width_ratio() const;

      /**
        * @brief Gets the height ratio of the object.
        * @return The object's height ratio.
      */
      float get_height_ratio() const;

      /**
        * @brief Sets the width and height ratios
        * @param r Ratios for width and height
      */
      void set_ratios(glm::vec2 r);
      
      void lock_screen_proportion(bool set = true);
      glm::mat4 *data();
      glm::mat4 const * const_data() const;
      glm::mat4 matrix() const;

      decomposed_transform decompose() const;
    };
  } // namespace graphics
} // namespace waifuengine

#endif