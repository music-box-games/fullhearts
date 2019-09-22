/******************************************************************************/
/*!
\file   inputargs.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\par    Project: Full Hearts
\date   9/21/2019 (Do you remember?)
\brief
    handles commandline options

\copyright    All content (c) 2019 Music Box Games, all rights reserved.
*/
/******************************************************************************/

#ifndef _WAIFU_INPUTARGS_H_
#define _WAIFU_INPUTARGS_H_

#include <set>
#include <wstr.hpp>
#include <boost/program_options.hpp>

namespace po = ::boost::program_options;

namespace WaifuEngine
{
    namespace utils
    {
        class argparse
        {
        private:
            static argparse * inst_;

            po::options_description desc_;
            po::variables_map vm_;
            argparse();

        public:
            static std::set<WaifuEngine::str> opts_;
            static argparse * get_instance();

            ~argparse();

            void add_opt(WaifuEngine::str opt, WaifuEngine::str msg);
            bool has_arg(WaifuEngine::str a);
            int parse(int argc, char ** argv);
            
        };
    }
}

#endif // !_WAIFU_INPUTARGS_H_