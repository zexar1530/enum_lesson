#pragma once

#include <boost/locale.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/version.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <string>
#include <vector>
#include <regex>

using namespace std;

enum class ProtocolType {
    HTTP,
    HTTPS
};

struct Links {
    ProtocolType protocol;
    string hostName;
    string query;
};

class StaticSpider {
public:
    static Links parse(const string& addr);
    static vector<string> readLinks(const string& content, const string& addr);
    static string readHtml(const Links& addr);
};
