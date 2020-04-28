#include <networking.hpp>

namespace waifuengine
{
namespace core
{
namespace networking
{
namespace example
{
#if 0
// 
// Example taken (stolen) from:
// https://www.boost.org/doc/libs/1_72_0/libs/beast/example/http/client/sync/http_client_sync.cpp
//

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/beast/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace beast = ::boost::beast;
namespace http = beast::http;
namespace net = ::boost::asio;
namespace tcp = net::ip::tcp;

void dl_test_file()
{
  int const version = 11;
  auto const host = "www.musicboxgames.net";
  auto const port = "80";
  auto const target = "/";

  // context is required to do any i/o
  boost::asio::io_context ioc;

  //  objects that actually perform i/o
  boost::asio::ip::tcp::resolver resolver(ioc);
  boost::beast::boost::beast::tcp_stream stream(ioc);

  // look up domain to get an ip
  auto const result = resolver.resolve(host, port);

  // setup a GET request
  http::request<http::string_body> req {http::verb::get, target, version};
  req.set(http::field::host, host);
  req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

  // send request
  http::write(stream, req);

  // response buffer
  beast::flap_buffer buffer;

  // response container
  http::response<http::dynamic_body> res;

  // receive response
  http::read(stream, buffer, res);

  // write message to cout
  //
  std::cout << res << std::endl;

  // close
  beast::error_code ec;
  stream.socket().shutdown(tcp::socket::shutdown_both, ec);
  if(ec && ec != beast::errc::not_connected)
  {
    throw beast::system_error{ec};
  }
}
#endif
} // namespace example
} // namespace networking
} // namespace core
} // namespace waifuengine
