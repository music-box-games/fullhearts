#include <unordered_set>

#include <engine.hpp>
#include <args.hpp>



static int handle_args(waifuengine::core::arg_parser const& ap)
{
    return 0;
}

int main(int argc, char ** argv)
{
    waifuengine::core::arg_parser ap;
    ap.add_flag("--timer-test");
    ap.parse(argc, argv);
    int result = handle_args(ap);
    if(result == -1) return 0;
    if(result == 0) {}
    else
    {
        // report error number
        return -1;
    }
    

    auto e = waifuengine::core::build_engine();

    while(waifuengine::core::engine::running)
    {
        e->update();
    }

    return 0;
}
