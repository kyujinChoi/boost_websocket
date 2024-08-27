#pragma once
#include "template/Parameter/Parameter.h"
#include <thread>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/config.hpp>

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>
#include <json/json.h> 

namespace beast = boost::beast;   // from <boost/beast.hpp>
namespace http = beast::http;     // from <boost/beast/http.hpp>
namespace net = boost::asio;      // from <boost/asio.hpp>
namespace websocket = boost::beast::websocket;
using tcp = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

class Websocket : public Parameter
{
    
    public:
        Websocket(){};
        ~Websocket(){};
        void join();
        void run();
    private:
        static void *acceptor_handler (void *pthis);
        static void *session_handler (void *pthis, tcp::socket &socket, std::shared_ptr<std::string const> const &doc_root);
        void acceptor();
        void fail(beast::error_code ec, char const *what);
        beast::string_view mime_type(beast::string_view path);
        std::string path_cat(beast::string_view base, beast::string_view path);
        void handleSession(tcp::socket &socket, std::shared_ptr<std::string const> const &doc_root);
        template <class Body, class Allocator> http::message_generator handleRequest(beast::string_view doc_root, http::request<Body, http::basic_fields<Allocator>> &&req);
        std::string getLidarData();
    private:
        std::unordered_map<std::string, boost::variant<int, std::string>> params;
        std::thread acceptor_th;
};
