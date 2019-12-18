#include <iostream>

#include <boost/program_options.hpp>

#include <args.hpp>
#include <hardware.hpp>
#include <tests.hpp>
#include <return_values.hpp>
#include <log.hpp>
#include <settings.hpp>

namespace we = ::waifuengine;
namespace po = boost::program_options;


namespace waifuengine
{
  namespace utils
  {
    namespace args
    {
      std::optional<int> parse(int argc, char ** argv)
      {
        {
          std::stringstream ss;
          ss << "Parsing command line. Args are:\n";
          for(int i = 0; i < argc; ++i)
          {
            ss << argv[i];
          }
          we::log::trace(ss.str());
        }

        po::options_description desc("Options");
        desc.add_options()
            ("help,h", "Prints help message.")
            ("test,t", "Runs engine tests. If this flag is specified, no other flags will be evaluated.")
            ("hardware-dump,hd", "Prints information about the hardware on the current machine.")
            ("pedantic,p", "Turns on pedantic debug output. Warning: This will be a crazy amount of information");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if(vm.count("help"))
        {
          std::cout << desc << '\n';
          return waifuengine::core::return_values::help;
        }
        if(vm.count("test"))
        {
          return ::waifuengine::tests::run_tests(argc, argv);
        }
        if(vm.count("hardware-dump"))
        {
          auto hwi = ::waifuengine::utils::hardware::get_hardware_info();
          ::std::cout << hwi << '\n';
          return ::waifuengine::core::return_values::hardware_dump;
        }
        if(vm.count("pedantic"))
        {
          we::settings::pedantic_debug = true;
        }

        // if no flags require ending the program, return with no value
        return {};
      }
    }
  }
}