/******************************************************************************/
/*!
\file   main.cpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\par    Project: Full Hearts
\date   9/20/2019
\brief  
    Main function for full hearts. Creates an engine object and runs it.

\copyright    All content (c) 2018 Music Box Games, all rights reserved.
*/
/******************************************************************************/

#include <inputargs.hpp>
#include <engine.hpp>
#include <typedef.hpp>

int main(int argc, char ** argv)
{
    WaifuEngine::utils::argparse * ap = WaifuEngine::utils::argparse::get_instance();
    if(ap->parse(argc, argv)) return 0;

    auto * e = WaifuEngine::engine::get_instance();
    
    return e->exec();
}
