#ifndef _WE_CIRCLE_HPP_
#define _WE_CIRCLE_HPP_

#include <glm/glm.hpp>

#include "SFML/Graphics.hpp"
#include "shape.hpp"

namespace waifuengine
{
  namespace graphics
  {
    class circle : public shape<0>
    {
    public:
      circle(int radius);
      virtual ~circle();

      virtual void draw();
      void radius(int r);
      int radius() const;

      virtual void fill_color(colors::color c);
      virtual colors::color fill_color() const;
      virtual void outline_color(colors::color c);
      virtual colors::color outline_color() const;

      void position(glm::vec2 pos);
      glm::vec2 position() const; 

    private:
      sf::CircleShape cs = sf::CircleShape(0);

    protected:
      colors::color fill_color_;
      colors::color outline_color_;
    };
  }
}

#endif