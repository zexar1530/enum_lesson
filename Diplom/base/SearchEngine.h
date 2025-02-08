#pragma once
#include "../Utils/Logger.h"
#include "../Database/Database.h"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>

#include <thread>
#include <fstream>
#include <iostream>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class SearchEngine : public std::enable_shared_from_this<SearchEngine> {
public:
    SearchEngine(Database& db, int port);

    void run();
    void stop();

private:
    boost::asio::io_context ioContext;
    boost::asio::ip::tcp::acceptor acceptor;
    boost::asio::steady_timer deadline;
    tcp::socket socket;
    http::request<http::string_body> request;
    http::response<http::string_body> response;
    beast::flat_buffer buffer;

    Database& db;
    int port;

    void readRequest();
    void processRequest();
    void doAccept();
    void checkDeadline();
    void writeResponse();
};
