/******************************************************************************/
/*!
\file   bitmanip.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
    Functions related to bit manipulation.

*/
/******************************************************************************/

#ifndef _W_BITMANIP_HPP_
#define _W_BITMANIP_HPP_

namespace waifuengine
{
    namespace utils
    {
        bool readbit(int const& pos);
        void setbit(int& data, int& mask);
        void setbit_n(int& data, int& pos);
    }
}

#endif // !_W_BITMANIP_HPP_
