#include <cstddef>
#include <functional>
#include <algorithm>
#include <random>
#include <string>
#include <climits>
#include <iterator>

#include <generators.hpp>

namespace waifuengine
{
namespace utils
{
// from: https://stackoverflow.com/questions/21842849/how-to-generate-a-random-string-in-c
std::string generate_string(int length)
{
  std::string const charset = "1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
  std::default_random_engine generator;
  std::uniform_int_distribution<int> dist(0, static_cast<int>(charset.size()) - 1);
  std::string result;
  std::generate_n(std::back_inserter(result), length, [&]() { return charset[dist(generator)];});
  return result;
}

int generate_int()
{
  std::default_random_engine gen;
  std::uniform_int_distribution<int> dist(0, INT_MAX);
  return dist(gen);
}

} // namespace utils
} // namespace waifuengine