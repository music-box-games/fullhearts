#include <iostream>

#include <gtest/gtest.h>

#include <tests.hpp>

#include <spacemanager.hpp>
#include <space.hpp>
#include <gameobject.hpp>

namespace waifuengine
{
    namespace tests
    {
        int run_tests(int argc, char ** argv)
        {
            ::testing::InitGoogleTest(&argc, argv);
            return RUN_ALL_TESTS();
        }

        TEST(GenericSuite, DefaultTest)
        {
            ASSERT_EQ(0, 0);
        }

        TEST(SpaceTests, BuildTest)
        {
            ::waifuengine::object_management::space_manager sm;
            sm.add_space("test space")->add_object("test object");
            ASSERT_EQ(sm.objects(), 1);
        }

        TEST(SpaceTests, DestroyTest)
        {
            std::string objname = "test object";
            ::waifuengine::object_management::space_manager sm;
            auto s = sm.add_space("test space");
            s->add_object(objname);
            ASSERT_EQ(sm.objects(), 1);
            s->remove_object(objname);
            ASSERT_EQ(sm.objects(), 0);
        }
    }
}
