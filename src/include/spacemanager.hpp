/******************************************************************************/
/*!
\file   spacemanager.hpp
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\par    Project: Full Hearts
\date   9/22/2019
\brief
    Manager that handles creation, updating, and destruction of spaces

\copyright    All content (c) 2019 Music Box Games, all rights reserved.
*/
/******************************************************************************/

#ifndef _WAIFU_SPACEMANAGER_H_
#define _WAIFU_SPACEMANAGER_H_

#include <unordered_map>
#include <memory>
#include <wstr.hpp>
#include <space.hpp>
#include <object.hpp>
#include <system.hpp>

namespace WaifuEngine
{
    namespace object_management
    {
        using space_map = std::unordered_map<WaifuEngine::str, space *>;

        class spacemanager : public system<spacemanager>
        {
        private:
            static spacemanager * instance_;

            space_map spaces_;
            spacemanager();
        public:
            SYS_NAME(spacemanager);

            static spacemanager * get_instance();

            virtual ~spacemanager();

            virtual void update(float dt) override;
            virtual void draw() const override;

            space * add_space(WaifuEngine::str name);
            void remove_space(WaifuEngine::str name);


            space_map& get_spaces();
        };
    }
}

#endif // !_WAIFU_SPACEMANGER_H_