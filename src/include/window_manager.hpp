#ifndef _WE_WINDOW_MANAGER_HPP_
#define _WE_WINDOW_MANAGER_HPP_

namespace waifuengine
{
  namespace graphics
  {
    class window_manager
    {
    public:
      window_manager();
      ~window_manager();

      void update();
      void clear();
      void display();
    };
  }
}

#endif