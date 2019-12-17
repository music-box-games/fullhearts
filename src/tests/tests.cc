#include <iostream>
#include <functional>
#include <filesystem>
#include <fstream>

#include <gtest/gtest.h>

#include <tests.hpp>

#include <spacemanager.hpp>
#include <space.hpp>
#include <gameobject.hpp>
#include <component.hpp>
#include <dummy.hpp>

#include <hardware.hpp>

#include <events.hpp>
#include <event_manager.hpp>

#include <utils.hpp>

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

        // TODO: move these into their respective parts rather than a separate file for all tests

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

        TEST(HardwareTests, RAMTest)
        {
            auto hwi = ::waifuengine::utils::hardware::get_hardware_info();
            EXPECT_NE(hwi.memory, 0);
        }

        TEST(EventTests, PrintEventTest)
        {
            class sender
            {
            public:
                void sendit(std::string m)
                {
                    events::cout_event e(m);
                    events::handle(&e);
                }
            };

            class receiver
            {
            public:
                std::stringstream ss;
            private:

                void message_handler(::waifuengine::events::event * e)
                {
                    auto ce = dynamic_cast<::waifuengine::events::cout_event *>(e);
                    ss << ce->message;
                }

            public:
                receiver()
                {
                    auto f = std::bind(&receiver::message_handler, this, std::placeholders::_1);
                    ::waifuengine::events::subscribe<::waifuengine::events::cout_event>(this, f);     
                }

                ~receiver()
                {
                    //::waifuengine::events::unsubscribe<::waifuengine::events::cout_event>(this);
                }
            };

            ::waifuengine::events::init();

            receiver r;
            sender s;
            s.sendit("REEE");
            ASSERT_EQ(std::string("REEE"), r.ss.str());

            ::waifuengine::events::shutdown();
        }

        TEST(UtilTests, FileParseTest)
        {
            std::string fname = "/WETESTTEXTFILE";
            std::ofstream tfile(fname);
            ASSERT_TRUE(tfile.is_open());
            int linecount = 5;
            for(int i = 0; i < linecount; ++i)
            {
                tfile << "line " << i << '\n';
            }
            tfile.close();
            auto v = ::waifuengine::utils::parse_file_to_vector(fname);
            ASSERT_EQ(linecount, v.size());
            for(auto const& s : v)
            {
                ASSERT_NE(s.size(), 0);
            }
            std::filesystem::remove(fname);
        }
    }
}
