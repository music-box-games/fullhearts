/******************************************************************************/
/*!
\file   
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\par    Project: Full Hearts
\date   
\brief

\copyright    All content (c) 2018 Music Box Games, all rights reserved.
*/
/******************************************************************************/

#ifndef _WAIFU_SYSTEM_H_
#define _WAIFU_SYSTEM_H_

#include <string>

#define SYS_NAME(x) static constexpr const char * NAME = #x

namespace WaifuEngine
{
    class base_system
    {
    private:
    public:
        const std::string NAME;

        base_system(const char * n) : NAME(n) {}
        base_system() = delete;
        virtual ~base_system() {}

        virtual void update(float dt) = 0;
        virtual void draw() const = 0;
    };

    template<typename S>
    class system : public base_system
    {
    private:
    public:
        system() : base_system(S::NAME) {}
        virtual ~system() {}

        virtual void update(float dt) override = 0;
        virtual void draw() const override = 0;
    };
}

#endif // !_WAIFU_SYSTEM_H_
