#ifndef _WE_WINDOW_HPP_
#define _WE_WINDOW_HPP_

#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

namespace waifuengine
{
  namespace graphics
  {
    class window
    {
    public:
      window(int width, int height, std::string title);
      ~window();

      void update();
      void clear();
      void display();

    private:
      int width_;
      int height_;
      std::string title_;

      std::shared_ptr<sf::RenderWindow> rw;
    };
  }
}

#endif