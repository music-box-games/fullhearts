/******************************************************************************/
/*!
\file   inputargs.cpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\par    Project: Full Hearts
\date   9/21/2019 (Do you remember?)
\brief
    handles commandline options

\copyright    All content (c) 2019 Music Box Games, all rights reserved.
*/
/******************************************************************************/

#include <iostream>
#include <inputargs.hpp>
#include <trace.hpp>
#include <utils.hpp>

namespace WaifuEngine
{
    namespace utils
    {
        argparse * argparse::inst_ = nullptr;
        std::set<WaifuEngine::string_type> argparse::opts_ = std::set<WaifuEngine::string_type>();

        argparse * argparse::get_instance()
        {
            if(!inst_) inst_ = new argparse();
            return inst_;
        }

        argparse::argparse() : desc_(po::options_description("Options"))
        {
            desc_.add_options()("help", "Shows help message.")("h", "Shows help message.");
        }

        argparse::~argparse() {}

        void argparse::add_opt(WaifuEngine::string_type opt, WaifuEngine::string_type msg)
        {
            desc_.add_options()(opt.c_str(), msg.c_str());
            desc_.add_options()();
        }

        int argparse::parse(int argc, char ** argv)
        {
            try
            {
#ifdef _DEBUG
                //WaifuEngine::trace::log("Beginning cmd parse");
#endif // _DEBUG
                po::store(po::parse_command_line(argc, argv, desc_), vm_); // can throw
#ifdef _DEBUG
                //WaifuEngine::trace::log("Found options:");
                po::notify(vm_);
#endif // _DEBUG
                if(vm_.count("help") || vm_.count("h"))
                {
                    //WaifuEngine::trace::log(desc_);
                    return 1;
                }
            }
            catch(const po::error& e)
            {
                //WaifuEngine::trace::error(e.what());
                return 1;
            }
            
            for(auto o : vm_)
            {
                WaifuEngine::sstream_type ss;
                ss << o.first;
                opts_.insert(ss.str());
            }

            return 0;
        }

        bool argparse::has_arg(WaifuEngine::string_type a)
        {
            return vm_.count(a);
        }
    }
}
