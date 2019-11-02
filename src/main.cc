#include <engine.hpp>

int main(int argc, char ** argv)
{
    auto e = waifuengine::core::build_engine();

    while(waifuengine::core::engine::running)
    {
        e->update();
    }

    return 0;
}
