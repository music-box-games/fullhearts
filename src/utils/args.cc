#include <iostream>

#include <boost/program_options.hpp>

#include <args.hpp>
#include <hardware.hpp>
#include <tests.hpp>

namespace waifuengine
{
  namespace utils
  {
    namespace args
    {
      std::optional<int> parse(int argc, char ** argv)
      {
        namespace po = boost::program_options;

        po::options_description desc("Options");
        desc.add_options()
        ("help,h", "Prints help message.")
        ("test,t", "Runs engine tests. If this flag is specified, no other flags will be evaluated.")
        ("hardware-dump,hd", "Prints information about the hardware on the current machine.");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if(vm.count("help"))
        {
          std::cout << desc << '\n';
          return help;
        }
        if(vm.count("test"))
        {
          return ::waifuengine::tests::run_tests(argc, argv);
        }
        if(vm.count("hardware-dump"))
        {
          auto hwi = ::waifuengine::utils::hardware::get_hardware_info();
          ::std::cout << hwi << '\n';
          return hardware_dump;
        }

        return {};
      }
    }
  }
}