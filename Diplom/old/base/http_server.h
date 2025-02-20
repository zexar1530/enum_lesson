#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>

#include <thread>
#include <fstream>
#include <iostream>
#include "PostgreDb.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class Serv : public std::enable_shared_from_this<Serv> {
public:
    Serv(PostgreDb& db, int port);
    void run();
    void stop();

private:
    boost::asio::io_context ioContext;
    tcp::acceptor acceptor;
    boost::asio::steady_timer deadline;
    tcp::socket socket;
    http::request<http::string_body> request;
    http::response<http::string_body> response;
    beast::flat_buffer buffer_/*{8192}*/;

    PostgreDb& db;
    int port;

    void checkDeadline();
    void writeResponse();
    void readRequest();
    void processRequest();
    void accept();
};
