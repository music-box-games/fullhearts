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

#include "include/engine.hpp"

int main(int argc, char ** argv)
{
    auto * e = WaifuEngine::engine::get_instance();
    
    return e->exec();
}