#include <args.hpp>
#include <log.hpp>

namespace waifuengine
{
    namespace core
    {
        arg_parser::arg_parser() 
        {

        }

        arg_parser::~arg_parser()
        {

        }

        void arg_parser::add_flag(std::string flag)
        {
            flags_[flag] = false;
        }

        bool arg_parser::has(std::string flag) const
        {
            return flags_.count(flag);
        }

        void arg_parser::parse(int argc, char ** argv)
        {
            for(int i = 0; i < argc; ++i)
            {
                if(flags_.count(argv[i]))
                {
                    flags_[argv[i]] = true;
                }
                else
                {
                    // TODO: fix this ::waifuengine::log::LOGERROR((std::string("Unrecognized flag: ") + std::string(argv[i])));
                }
            }
        }
    }
}