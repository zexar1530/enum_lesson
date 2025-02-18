#include "StaticSpider.h"


namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

Links StaticSpider::parse(const string& addr) {
    const regex urlRegex(R"(^(https?)://([^/]+)(/?.*)$)");
    smatch match;

    if (!regex_match(addr, match, urlRegex)) {
        throw invalid_argument("Неверный формат адреса");
    }

    ProtocolType protocol = (match[1] == "https") ? ProtocolType::HTTPS : ProtocolType::HTTP;
    string hostName = match[2];
    string query = match[3].str().empty() ? "/" : match[3].str();

    return { protocol, hostName, query };
}
vector<string> StaticSpider::readLinks(const string& content, const string& addr) {
    vector<string> links;
    regex hrefregex(R"(<a\s+[^>]*href=["']([^"']+)["'])", regex::icase);
    auto begin = sregex_iterator(content.begin(), content.end(), hrefregex);
    auto end = sregex_iterator();

    for (auto it = begin; it != end; ++it) {
        string link = (*it)[1].str();

        size_t hashPos = link.find('#');
        if (hashPos != string::npos) {
            link = link.substr(0, hashPos);
        }

        if (link.empty()) {
            continue;
        }

        if (link.find("http://") != 0 && link.find("https://") != 0) {
            if (link.front() == '/') {
                Links baseParsed = parse(addr);
                link = (baseParsed.protocol == ProtocolType::HTTPS ? "https://" : "http://") + baseParsed.hostName + link;
            }
            else {
                link = addr + "/" + link;
            }
        }

        if (!link.empty() && link.back() == '/') {
            link.pop_back();
        }

        links.push_back(link);
    }
    return links;
}

string StaticSpider::readHtml(const Links& addr) {
    net::io_context ioc;

    try {
        if (addr.protocol == ProtocolType::HTTPS) {
            net::ssl::context sslContext(net::ssl::context::tlsv12_client);
            sslContext.set_verify_mode(net::ssl::verify_none);
            sslContext.set_default_verify_paths();
            
            beast::ssl_stream<beast::tcp_stream> stream(ioc, sslContext);
            tcp::resolver resolver(ioc);
            auto const results = resolver.resolve(addr.hostName, "https");

            beast::get_lowest_layer(stream).connect(results);
            if (!SSL_set_tlsext_host_name(stream.native_handle(), addr.hostName.c_str())) {
                throw beast::system_error(net::error::invalid_argument, "Failed to set SNI host name");
            }

            stream.handshake(net::ssl::stream_base::client);
            http::request<http::string_body> req{ http::verb::get, addr.query, 11 };
            req.set(http::field::host, addr.hostName);
            req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

            http::write(stream, req);

            beast::flat_buffer buffer;
            http::response<http::string_body> res;
            http::read(stream, buffer, res);

            return res.body();
        }
        else {
            tcp::resolver resolver(ioc);
            beast::tcp_stream stream(ioc);

            auto const results = resolver.resolve(addr.hostName, "80");
            stream.connect(results);

            http::request<http::string_body> req{ http::verb::get, addr.query, 11 };
            req.set(http::field::host, addr.hostName);
            req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

            http::write(stream, req);   //---------
 
            beast::flat_buffer buffer;
            http::response<http::string_body> res;
            http::read(stream, buffer, res);
            return res.body();
        }
    }
    catch (const boost::system::system_error& e) {
        return "";
    }
}