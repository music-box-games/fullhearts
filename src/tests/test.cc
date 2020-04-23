/******************************************************************************/
/*!
\file   tests.cc
\author Ryan Hanson
\par    email: iovita\@musicboxgames.net
\brief
    Engine tests

*/
/******************************************************************************/

#include <iostream>
#include <functional>
#include <fstream>
#include <sstream>

#include <tests.hpp>
#include <fs_util.hpp>
#include <serialization.hpp>
#include <component.hpp>
#include <dummy.hpp>
#include <gameobject.hpp>
#include <spacemanager.hpp>
#include <space.hpp>
#include <scenes.hpp>
#include <scenemanager.hpp>
#include <scenelist.hpp>


namespace we = ::waifuengine;

namespace waifuengine
{
namespace tests
{

int run_tests(int argc, char **argv)
{
    // create temp folder for test assets
    std::stringstream ss;
    ss << we::utils::get_exe_path() << "\\.tests";
    ::fs::create_directory(ss.str());
    // init google test and run tests
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    // delete temp folder
    ::fs::remove_all(ss.str());
    return result;
}

// serialization tests

static std::stringstream create_serialize_test_folder()
{
    std::stringstream ss;
    ss << utils::get_exe_path() << "\\.tests\\serialization";
    if(!::fs::exists(ss.str()))
    {
        ::fs::create_directory(ss.str());
    }
    return ss;
}



TEST(SerializationTest, SerializeBaseClass)
{
    // create object to serialze
    we::core::serialization::test::test_serialize_object o(1, 2, 3, "Hello");
    // create test folder, if it doesn't already exist
    auto ss = create_serialize_test_folder();
    // create archive
    ss << "\\base_object";
    {
        std::ofstream stream(ss.str());
        ::boost::archive::text_oarchive arch(stream);
        // write instance to archive
        arch << o;
    }
    // load archive into new object
    we::core::serialization::test::test_serialize_object i(0,0,0,"");
    {
        std::ifstream stream(ss.str());
        ::boost::archive::text_iarchive arch(stream);
        // read from archive;
        arch >> i;
    }
    
    ASSERT_TRUE(o == i);
}

TEST(SerializationTest, SerializeDerivedClass)
{
    // create the object
    we::core::serialization::test::derived_test_serialize_object o(1, 2, 3, "Hello", 4);
    // create folder if not existing
    auto ss = create_serialize_test_folder();
    // create archive
    ss << "\\derived_object";
    {
        std::ofstream stream(ss.str());
        ::boost::archive::text_oarchive arch(stream);
        // write instance to archive
        arch << o;
    }
    // load archive to fresh object
    we::core::serialization::test::derived_test_serialize_object i(0,0,0, "", 0);
    {
        std::ifstream stream(ss.str());
        ::boost::archive::text_iarchive arch(stream);
        // write instance to archive
        arch >> i;
    }

    ASSERT_TRUE(o == i);
}

TEST(SerializationTest, SerializeEmptyObject)
{
    we::object_management::space_manager spm;
    auto sp = spm.add_space("test");
    auto objo = sp->add_object("test");

    auto ss = create_serialize_test_folder();
    ss << "\\empty_object";
    {
        std::ofstream stream(ss.str());
        ::boost::archive::text_oarchive arch(stream);
        arch << objo;
    }
    auto obji = sp->add_object("");
    EXPECT_FALSE(*objo == *obji);
    {
        std::ifstream stream(ss.str());
        ::boost::archive::text_iarchive arch(stream);
        arch >> obji;
    }
    EXPECT_TRUE(*objo == *obji);
}



TEST(SerializationTest, SerializeObject)
{
    we::object_management::space_manager spm;
    auto sp = spm.add_space("test");
    auto objo = sp->add_object("test");
    auto d = objo->add_component<components::dummy>();

    auto ss = create_serialize_test_folder();
    ss << "\\object";
    {
        std::ofstream stream(ss.str());
        ::boost::archive::text_oarchive arch(stream);
        arch << objo;
    }
    auto obji = sp->add_object("");
    EXPECT_FALSE(*objo == *obji);
    {
        std::ifstream stream(ss.str());
        ::boost::archive::text_iarchive arch(stream);
        arch >> obji;
    }
    EXPECT_TRUE(*objo == *obji);
}



TEST(SerializationTest, SerializeSceneManager)
{
    we::scenes::impl::scene_manager sm = we::scenes::impl::scene_manager();
    sm.load<we::scenes::test::scene_serializationtest>();

    auto ss = create_serialize_test_folder();
    ss << "\\scenemgr";
    {
        std::ofstream stream(ss.str());
        ::boost::archive::text_oarchive arch(stream);
        arch << sm;
    }
    we::scenes::impl::scene_manager sm2 = we::scenes::impl::scene_manager();
    EXPECT_FALSE(sm == sm2);
    {
        std::ifstream stream(ss.str());
        ::boost::archive::text_iarchive arch(stream);
        arch >> sm2;
    }
    EXPECT_TRUE(sm == sm2);
}

} // namespace tests
} // namespace waifuengine