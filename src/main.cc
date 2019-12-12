#include <unordered_set>

#include <boost/program_options.hpp>

#include <engine.hpp>
#include <tests.hpp>


int main(int argc, char ** argv)
{
    namespace po = boost::program_options;

    po::options_description desc("Options");
    desc.add_options()
    ("test,t", "Runs engine tests.");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    if(vm.count("test"))
    {
        return waifuengine::tests::run_tests(argc, argv);
    }

    auto e = waifuengine::core::build_engine();

    while(waifuengine::core::engine::running)
    {
        e->update();
    }

    return 0;
}
