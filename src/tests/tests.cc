#include <iostream>

#include <gtest/gtest.h>

#include <tests.hpp>

#include <spacemanager.hpp>
#include <space.hpp>
#include <gameobject.hpp>
#include <component.hpp>
#include <dummy.hpp>

#include <hardware.hpp>


// TODO: a lot of this can be improved by sharing resources
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
            sm.add_space("test space");
            ASSERT_EQ(sm.spaces(), 1);
        }

        TEST(SpaceTests, DestroyTest)
        {
            std::string spname = "test space";
            ::waifuengine::object_management::space_manager sm;
            sm.add_space(spname);
            ASSERT_EQ(sm.spaces(), 1);
            sm.remove_space(spname);
            ASSERT_EQ(sm.spaces(), 0);
        }

        TEST(ObjectTests, BuildTest)
        {
            ::waifuengine::object_management::space_manager sm;
            sm.add_space("test space")->add_object("test object");
            ASSERT_EQ(sm.objects(), 1);
        }

        TEST(ObjectTests, DestroyTest)
        {
            ::waifuengine::object_management::space_manager sm;
            auto s = sm.add_space("test space");
            ASSERT_EQ(sm.spaces(), 1);
            s->add_object("test object");
            ASSERT_EQ(sm.objects(), 1);
            s->remove_object("test object");
        }

        TEST(ComponentTests, BuildTest)
        {
            ::waifuengine::object_management::space_manager sm;
            sm.add_space("test space")->add_object("test object")->add_component<::waifuengine::components::dummy>();
            ASSERT_EQ(sm.components(), 1);
        }

        TEST(ComponentTests, DestroyTest)
        {
            ::waifuengine::object_management::space_manager sm;
            auto s = sm.add_space("test space");
            ASSERT_EQ(sm.spaces(), 1);
            auto o = s->add_object("test object");
            ASSERT_EQ(sm.objects(), 1);
            auto c = o->add_component<::waifuengine::components::dummy>();
            ASSERT_EQ(sm.components(), 1);
            o->remove_component<::waifuengine::components::dummy>();
            ASSERT_EQ(sm.components(), 0);
        }

        TEST(HardwareTests, CPUIDTest)
        {
            auto hwi = ::waifuengine::utils::hardware::get_hardware_info();
            EXPECT_NE(hwi.cpu.arch.size(), 0);
            EXPECT_NE(hwi.cpu.type.size(), 0);
            EXPECT_NE(hwi.cpu.cores, 0);
        }

        TEST(HardwareTests, GPUIDTest)
        {
            auto hwi = ::waifuengine::utils::hardware::get_hardware_info();
            EXPECT_NE(hwi.gpu.make.size(), 0);
            EXPECT_NE(hwi.gpu.model.size(), 0);
        }
    }
}
