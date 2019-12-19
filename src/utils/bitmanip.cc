/******************************************************************************/
/*!
\file   bitmanip.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
    Bit manipulation functions

*/
/******************************************************************************/

#include <bitmanip.hpp>

namespace waifuengine
{
    namespace utils
    {
        bool readbit(int& data, int& pos)
        {
            return (data & (1 << pos));
        }

        void setbit(int& data, int& mask)
        {
            data |= mask;
        }

        void setbit_n(int& data, int& pos)
        {
            data |= (1 << pos);
        }
    }
    
}
