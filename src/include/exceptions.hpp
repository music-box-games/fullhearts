#ifndef _WE_EXCEPTIONS_HPP_
#define _WE_EXCEPTIONS_HPP_

#include <exception>
#include <string>

namespace waifuengine
{
  namespace core
  {
    namespace exceptions
    {
      class exception : public std::exception
      {
      protected:
        std::string message;
      public:
        exception();
        exception(const char *  m);
        exception(std::string const& m);
        virtual ~exception();
        virtual const char * what() const override;
        virtual void what(const char * m);
        virtual void what(std::string const& m);
      };

      class unimplemented : public exception 
      {
      public:
        unimplemented();
        unimplemented(const char * m);
        unimplemented(std::string const& m);
        ~unimplemented();
      };
    }
  }
}

#endif // !_WE_EXCEPTIONS_HPP_