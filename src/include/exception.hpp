#ifndef _WE_EXCEPTION_HPP_
#define _WE_EXCEPTION_HPP_

#include <exception>

#define UNIMPLEMENTED_EXCEPTION() ::waifuengine::core::_unimplemented_exception(__func__)

namespace waifuengine
{
  namespace core
  {
    class _unimplemented_exception : public std::exception
    {
    private:
      const char * message;
    public:
      _unimplemented_exception(const char * func);
      virtual ~_unimplemented_exception();

      virtual const char * what() const;
    };
  }
}

#endif