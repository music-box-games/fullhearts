#include <array>
#include <string_view>

#include <engine.hpp>
#include <args.hpp>

using namespace std::literals;
using namespace std::string_view_literals;
using namespace std::literals::string_view_literals;

static constexpr std::array<std::string_view, 1> flags = 
{
    "--timer-test"sv,
};

static void handle_args(waifuengine::core::arg_parser const& ap)
{

}

int main(int argc, char ** argv)
{
    waifuengine::core::arg_parser ap;
    ap.add_flag("--timer-test");
    ap.parse(argc, argv);
    handle_args(ap);

    auto e = waifuengine::core::build_engine();

    while(waifuengine::core::engine::running)
    {
        e->update();
    }

    return 0;
}
