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
#include <random>

#include <dummy.hpp>
#include <tests.hpp>
#include <fs_util.hpp>
#include <component.hpp>
#include <gameobject.hpp>
#include <spacemanager.hpp>
#include <space.hpp>
#include <scenes.hpp>
#include <scenemanager.hpp>
#include <scenelist.hpp>
#include <settings.hpp>
#include "num_utils.hpp"
#include "utils.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
namespace tests
{

  constexpr float WW = 1920.0f;
  constexpr float WH = 1080.0f;
  constexpr float ERROR_MARGIN = 0.01f;

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




TEST(ConversionTests, ByteTableConversions)
{
  {
    constexpr unsigned long double BYTES_IN = 1024.0;
    constexpr unsigned long double EXPECTED_KB_OUT = 1.0;
    unsigned long double actual_out = utils::byte_conversion<utils::byte_table::byte, utils::byte_table::kilobyte>(BYTES_IN);
    EXPECT_EQ(EXPECTED_KB_OUT, actual_out);
  }
  {
    constexpr unsigned long double KB_IN = (1024.0 * 1024.0) * 2.0;
    constexpr unsigned long double EXPECTED_GB_OUT = 2.0;
    unsigned long double actual_out = utils::byte_conversion<utils::byte_table::kilobyte, utils::byte_table::gigabyte>(KB_IN);
    EXPECT_EQ(EXPECTED_GB_OUT, actual_out);
  }
  {
    constexpr unsigned long double GB_IN = 512.0;
    constexpr unsigned long double EXPECTED_TB_OUT = 0.5;
    unsigned long double actual_out = utils::byte_conversion<utils::byte_table::gigabyte, utils::byte_table::terabyte>(GB_IN);
    EXPECT_EQ(EXPECTED_TB_OUT, actual_out);
  }
}

} // namespace tests
} // namespace waifuengine
