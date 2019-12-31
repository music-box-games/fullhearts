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

#include <boost/program_options.hpp>

#include <args.hpp>
#include <engine.hpp>
#include <tests.hpp>
#include <hardware.hpp>

namespace we = ::waifuengine;

int main(int argc, char ** argv)
{
    auto ret = waifuengine::utils::args::parse(argc, argv);
    if(ret.has_value())
    {
        return ret.value();
    }

    std::unique_ptr<waifuengine::core::engine> e = waifuengine::core::build_engine();
    e->load_initial_scene();


    while(::waifuengine::core::engine::running)
    {
        e->update();
    }

    return 0;
}
