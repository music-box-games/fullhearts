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
#include <gameobject.hpp>

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

TEST(SerializationTest, SerlilizeDerivedClass)
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

TEST(SerializationTest, SerializeEmptyGameObject)
{

}

} // namespace tests
} // namespace waifuengine