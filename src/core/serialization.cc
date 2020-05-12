#include <serialization.hpp>
#include <tests.hpp>
#include <fs_util.hpp>

namespace we = ::waifuengine;

namespace waifuengine
{
namespace core
{
namespace serialization
{
namespace test
{
test_serialize_object::test_serialize_object(int a, int b, int c, std::string t) : a(a), b(b), c(c), text(t) {}

bool test_serialize_object::operator==(test_serialize_object const& rhs)
{
  return (a == rhs.a) && (b == rhs.b) && (c == rhs.c) && (text == rhs.text);
}

derived_test_serialize_object::derived_test_serialize_object(int a, int b, int c, std::string t, int d) : test_serialize_object(a, b, c, t), d(d) {}

bool derived_test_serialize_object::operator==(test_serialize_object const& r)
{
  test_serialize_object& c_removed = const_cast<test_serialize_object&>(r);
  derived_test_serialize_object * rh = dynamic_cast<derived_test_serialize_object*>(&c_removed);
  if(rh)
  {
    auto rhs = *rh;
    return (a == rhs.a) && (b == rhs.b) && (c == rhs.c) && (d == rhs.d) && (text == rhs.text);
  }
  else return false;
}

} // namespace test
} // namespace serialization
} // namespace core
} // namespace waifuengine