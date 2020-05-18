/******************************************************************************/
/*!
\file   main.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
    Main. It's main idk. Builds and updates the engine.

*/
/******************************************************************************/

#include <iostream>
#include <unordered_set>

#include <args.hpp>
#include <engine.hpp>
#include <tests.hpp>
#include <utils.hpp>

#define CATCH

namespace we = ::waifuengine;

int main(int argc, char ** argv)
{
  std::unique_ptr<waifuengine::core::engine> e;
  #ifdef CATCH
  try
  #endif
  {
    auto ret = waifuengine::utils::args::parse(argc, argv);
    if(ret.has_value())
    {
        return ret.value();
    }

    e = waifuengine::core::build_engine();
    e->load_initial_scene();


    while(::waifuengine::core::engine::running)
    {
        e->update();
    }
    return 0;
  }
  #ifdef CATCH
  catch(const std::exception& ex)
  {
   // notify
   we::utils::notify(we::utils::notification_type::mb_ok, "Uncaught Exception", ex.what());
   return -1;
  }
  #endif
}
