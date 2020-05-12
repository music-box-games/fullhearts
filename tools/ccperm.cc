#include <sstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

template<class T>
void dumpvec(std::vector<T> const& v, std::stringstream& ss)
{
  std::for_each(v.begin(), v.end(), [&ss](T const& t) -> void {
    ss << t << ' ';
  });
}

int main(int argc, char ** argv)
{
  std::vector<std::string> args;
  for(int i = 1; i < argc; ++i)
  {
    args.push_back(argv[i]);
  }
  std::stringstream ss;

  do
  {
    dumpvec(args, ss);
  }while(std::next_permutation(args.begin(), args.end()));

  std::cout << ss.str() << std::endl;

  return 0;
}