#ifndef _WE_TEXTSPRITE_HPP_
#define _WE_TEXTSPRITE_HPP_

#include <string>

#include <component.hpp>
#include <text_image.hpp>

namespace waifuengine
{
  namespace graphics
  {
    class textsprite : public waifuengine::components::component<textsprite>
    {
    public:
      COMPONENT_NAME(textsprite);
      COMPONENT_TYPE(textsprite);

      textsprite();
      virtual ~textsprite();

      void text(std::string t);
      std::string text() const;

      virtual void update(float dt);
      virtual void draw() const;

    private:
      text_image ti;
    };
  }
}

#endif 