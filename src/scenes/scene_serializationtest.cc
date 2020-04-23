
#include <scene_serializationtest.hpp>

#include <spacemanager.hpp>
#include <space.hpp>
#include <gameobject.hpp>
#include <component.hpp>
#include <dummy.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace scenes
{
namespace test
{
  scene_serializationtest::scene_serializationtest() : scene(std::string(NAME))
  {
    // make some dumb objects
    auto sp1 = manager.add_space("test1");
    auto sp2 = manager.add_space("test2");
    auto sp3 = manager.add_space("test3");

    auto obj1 = sp1->add_object("test1");
    auto d1 = obj1->add_component<we::components::dummy>();
    d1->set_data(1);

    auto obj2 = sp2->add_object("test2");
    auto d2 = obj2->add_component<we::components::dummy>();
    d2->set_data(2);
    auto obj3 = sp2->add_object("test3");
    auto d3 = obj3->add_component<we::components::dummy>();
    d3->set_data(3);

    auto obj4 = sp3->add_object("test4");
    auto d4 = obj4->add_component<we::components::dummy>();
    d4->set_data(4);
    auto obj5 = sp3->add_object("test5");
    auto d5 = obj5->add_component<we::components::dummy>();
    d5->set_data(5);
    auto obj6 = sp3->add_object("test6");
    auto d6 = obj6->add_component<we::components::dummy>();
    d6->set_data(5);
  }

  scene_serializationtest::~scene_serializationtest()
  {

  }
}
} // namespace scenes
} // namespace waifuengine

BOOST_CLASS_EXPORT_IMPLEMENT(we::scenes::test::scene_serializationtest);