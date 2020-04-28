#ifndef _WE_NETWORKING_HPP_
#define _WE_NETWORKING_HPP_

#include <atomic>

namespace waifuengine
{
  namespace core
  {
    namespace networking
    {
      namespace impl
      {

      }
      // handle to a connection to website, is returned from a connect function so that the connnection
      // can be handled async and other threads can use the handle to check the status of the connection
      class session_handle
      {        
      public:
        session_handle();
        ~session_handle();
      };

      class downloader
      {
      public:
        downloader();
        ~downloader();
      };

      namespace test
      {
        enum class return_codes // return codes
        {

        };
      }
    }
  }
}

#endif
