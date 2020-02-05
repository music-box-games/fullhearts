/******************************************************************************/
/*!
\file   textsprite.hpp
\author Ryan Hanson
\par    email: iovita@musicboxgames.net
\brief
  Type of sprite for images of rendered text

*/
/******************************************************************************/

#ifndef _WE_TEXTSPRITE_HPP_
#define _WE_TEXTSPRITE_HPP_

#include <string>
#include <memory>

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

      virtual void update(float dt);
      virtual void draw() const;

      void set_text(std::string s);

    private:
      std::shared_ptr<text_image> ti;
    };
  }
}

#endif 