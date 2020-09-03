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
#include <serialization.hpp>
#include <component.hpp>
#include <gameobject.hpp>
#include <spacemanager.hpp>
#include <space.hpp>
#include <scenes.hpp>
#include <scenemanager.hpp>
#include <scenelist.hpp>
#include <settings.hpp>
#include "coordinates.hpp"
#include "num_utils.hpp"

namespace we = ::waifuengine;

namespace waifuengine
{
namespace tests
{

  constexpr float WW = 1920.0f;
  constexpr float WH = 1080.0f;
  constexpr float ERROR_MARGIN = 0.1f;


static graphics::screen_coordinates_2d random_screen_pos()
{
  return graphics::screen_coordinates_2d(utils::generate_random_float_between(-1.0f, 1.0f), utils::generate_random_float_between(-1.0f, 1.0f));
}

static graphics::window_coordinates_2d random_world_pos()
{
  return graphics::window_coordinates_2d(utils::generate_random_int_between(0, static_cast<int>(WW)), utils::generate_random_int_between(0, static_cast<int>(WH)));
}

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



TEST(ConversionTest, WorldCoordinatesToScreenCoordinates)
{
  // check that world coordinates are properly converted into screen coordinates
  // check each corner and dead center
  graphics::window_coordinates_2d world_pos;
  graphics::screen_coordinates_2d expected_result;
  graphics::screen_coordinates_2d actual_result;

  // center
  world_pos = {WW / 2.0f, WH / 2.0f}; // center of screen in world coordinates is half of the width and height
  expected_result = {0.f, 0.f};
  actual_result = graphics::window_coordinates_to_screen_coordinates(world_pos, WW, WH);
  ASSERT_TRUE(graphics::lax_coordinate_compare(expected_result, actual_result, ERROR_MARGIN));

  // bottom left
  world_pos = {0.f,0.f}; // bottom left is 0,0 in world coordinates, that way no negative numbers for being on screen
  expected_result = {-1.f, -1.f};
  actual_result = graphics::window_coordinates_to_screen_coordinates(world_pos, WW, WH);
  ASSERT_TRUE(graphics::lax_coordinate_compare(expected_result, actual_result, ERROR_MARGIN));

  // top left
  world_pos = {0.f, WH}; // top left, 0 in x, max in y
  expected_result = {-1.f, 1.f};
  actual_result = graphics::window_coordinates_to_screen_coordinates(world_pos, WW, WH);
  ASSERT_TRUE(graphics::lax_coordinate_compare(expected_result, actual_result, ERROR_MARGIN));

  // top right
  world_pos = {WW, WH}; // max in each direction
  expected_result = {1.f,1.f};
  actual_result = graphics::window_coordinates_to_screen_coordinates(world_pos, WW, WH);
  ASSERT_TRUE(graphics::lax_coordinate_compare(expected_result, actual_result, ERROR_MARGIN));
  

  // bottom right
  world_pos = {WW, 0.f};
  expected_result = {1.f, -1.f};
  actual_result = graphics::window_coordinates_to_screen_coordinates(world_pos, WW, WH);
  ASSERT_TRUE(graphics::lax_coordinate_compare(expected_result, actual_result, ERROR_MARGIN));

  // random pos
  world_pos = random_world_pos();
  expected_result = { world_pos.x / WW, world_pos.y / WH};
  actual_result = graphics::window_coordinates_to_screen_coordinates(world_pos, WW, WH);
  ASSERT_TRUE(graphics::lax_coordinate_compare(expected_result, actual_result, ERROR_MARGIN));
}

TEST(ConversionTest, ScreenCoordinatesToWorldCoordinates)
{
  // check that world coordinates are properly converted into screen coordinates
  // check each corner and dead center
  graphics::screen_coordinates_2d screen_pos;
  graphics::window_coordinates_2d expected_result;
  graphics::window_coordinates_2d actual_result;

  // center
  screen_pos = {0.f, 0.f};
  expected_result = {WW / 2.0f, WH / 2.0f};
  actual_result = graphics::screen_coordinates_to_window_coordinates(screen_pos, WW, WH);
  ASSERT_TRUE(graphics::lax_coordinate_compare(expected_result, actual_result, ERROR_MARGIN));

  // bottom left
  screen_pos = {-1.f, -1.f};
  expected_result = {0.f,0.f};
  actual_result = graphics::screen_coordinates_to_window_coordinates(screen_pos, WW, WH);
  ASSERT_TRUE(graphics::lax_coordinate_compare(expected_result, actual_result, ERROR_MARGIN));

  // top left
  screen_pos = {-1.f, 1.f};
  expected_result = {0.f, WH};
  actual_result = graphics::screen_coordinates_to_window_coordinates(screen_pos, WW, WH);
  ASSERT_TRUE(graphics::lax_coordinate_compare(expected_result, actual_result, ERROR_MARGIN));

  // top right
  screen_pos = {1.f,1.f};
  expected_result = {WW, WH}; 
  actual_result = graphics::screen_coordinates_to_window_coordinates(screen_pos, WW, WH);
  ASSERT_TRUE(graphics::lax_coordinate_compare(expected_result, actual_result, ERROR_MARGIN));
  

  // bottom right
  screen_pos = {1.f, -1.f};
  expected_result = {WW, 0.f};
  actual_result = graphics::screen_coordinates_to_window_coordinates(screen_pos, WW, WH);
  ASSERT_TRUE(graphics::lax_coordinate_compare(expected_result, actual_result, ERROR_MARGIN));

  //  // random pos
  //screen_pos = random_screen_pos();
  //expected_result = { screen_pos.x * WW, screen_pos.y * WH};
  //actual_result = graphics::screen_coordinates_to_window_coordinates(screen_pos, WW, WH);
  //ASSERT_TRUE(graphics::lax_coordinate_compare(expected_result, actual_result, ERROR_MARGIN));
}

} // namespace tests
} // namespace waifuengine