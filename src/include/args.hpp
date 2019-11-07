#ifndef _W_ARGS_HPP_
#define _W_ARGS_HPP_

#include <unordered_map>
#include <string>

namespace waifuengine
{
    namespace core
    {
        // TODO: this currently only accepts flags with no args
        class arg_parser
        {
        private:
            typedef std::unordered_map<std::string, bool> flaglist;
            flaglist flags_;

        public:
            arg_parser();
            ~arg_parser();

            void add_flag(std::string flag);
            bool has(std::string flag) const;
            void parse(int argc, char ** argv);
        };
    }
}

#endif // !_W_ARGS_HPP_