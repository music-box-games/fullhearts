#include <unordered_set>

#include <boost/program_options.hpp>

#include <args.hpp>
#include <engine.hpp>
#include <tests.hpp>


int main(int argc, char ** argv)
{
    auto ret = waifuengine::utils::args::parse(argc, argv);
    if(ret.has_value())
    {
        return ret.value();
    }

    auto e = waifuengine::core::build_engine();

    while(waifuengine::core::engine::running)
    {
        e->update();
    }

    return 0;
}
