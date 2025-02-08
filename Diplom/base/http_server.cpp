#include "http_server.h"


string urlUtf(const string& encoded) {
    std::string res;
    size_t i = 0;

    while (i < encoded.size()) {
        if (encoded[i] == '%') {
            if (i + 2 < encoded.size() && isxdigit(encoded[i + 1]) && isxdigit(encoded[i + 2])) {
                int hex = 0;
                std::istringstream(encoded.substr(i + 1, 2)) >> std::hex >> hex;
                res += static_cast<char>(hex);
                i += 3;
            }
            else {
                res += '%';
                i++;
            }
        }
        else if (encoded[i] == '+') {
            res += ' ';
            i++;
        }
        else {
            res += encoded[i];
            i++;
        }
    }

    return res;
}

Serv::Serv(PostgreDb& db, int port)
    : db(db), port(port), acceptor(ioContext, tcp::endpoint(tcp::v4(), port)),
    deadline(ioContext), socket(ioContext){
}

void Serv::accept() {
    if (!acceptor.is_open()) return;

    acceptor.async_accept(socket, [this](beast::error_code ec) {
        try {
            if (!ec) {
                readRequest();
                checkDeadline();
            }
            accept();
        }
        catch (const std::exception& e) {
            throw runtime_error("Ошибка создания Acceptoра " + string(e.what()));
        }
        });
}

void Serv::checkDeadline() {
    auto self = shared_from_this();

    deadline.async_wait(
        [self](beast::error_code ec)
        {
            if (!ec)
            {
                self->socket.close(ec);
            }
        });
}

void Serv::readRequest() {
    auto self = shared_from_this();
    request = {};
    http::async_read(socket, buffer_, request, [self](beast::error_code ec, size_t bytes_transferred) {
        boost::ignore_unused(bytes_transferred);
        if (!ec) self->processRequest();
        });
}

void Serv::writeResponse() {
    auto self = shared_from_this();

    response.content_length(response.body().size());

    http::async_write(socket, response, [self](beast::error_code ec, size_t) {
    if (!ec) self->readRequest();
        else self->socket.close();
    self->deadline.cancel();
    });
}

void Serv::processRequest() {
    try {
        string html_content;
        string query;
        string results_html;

        std::ifstream f("form.html");
        if (!f.is_open()) {
            response.result(http::status::internal_server_error);
            response.body() = "<html><body><h1>Ошибка формы</h1></body></html>";
            writeResponse();
            return;
        }
        html_content = string((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());

        if (request.method() == http::verb::post) {
            string body = request.body();
            auto pos = body.find("query=");
            if (pos != string::npos) {
                query = body.substr(pos + 6);
                query = urlUtf(query);
                wstring_convert<codecvt_utf8_utf16<wchar_t>> wc;
                wstring w = wc.from_bytes(query);
                locale loc("ru_RU.UTF-8");
                for (auto& c : w) {
                    c = tolower(c, loc);
                }
                query = wc.to_bytes(w);
            }

            vector<string> words;
            istringstream s_w(query);
            string w;
            while (s_w >> w) {
               /* w.erase(remove_if(w.begin(), w.end(), ispunct), w.end());
                w = boost::locale::conv::from_utf(w, "Windows-1251");
                if (!w.empty()) {
                    words.push_back(w);
                }*/
                words.push_back(w);
            }

            auto results = db.getDocs(words);

            if (results.empty()) {
                results_html = "<li>No result......</li>";
            }
            else {
                for (const auto& [http, count] : results) {
                    results_html += "<li><a href=\"" + http + "\">" + http + "</a> - Count: " + std::to_string(count) + "</li>";
                }
            }
        }

        size_t pos_q = html_content.find("{{query}}");
        if (pos_q != string::npos) {
            html_content.replace(pos_q, 9, query);
        }

        size_t pos_r = html_content.find("{{results}}");
        if (pos_r != string::npos) {
            html_content.replace(pos_r, 11, results_html);
        }

        response.result(http::status::ok);
        response.set(http::field::content_type, "text/html");
        response.body() = html_content;
        writeResponse();
    }
    catch (const std::exception& e){
        response.result(http::status::internal_server_error);
        response.body() = "<html><body><h1>Ошибка сервера</h1></body></html>";
        writeResponse();
    }

}
void Serv::run() {
    try {
        accept();
        ioContext.run();
    }
    catch (const std::exception& e) {
        throw runtime_error("Ошибка запуска сервера" + string(e.what()));
    }
}

void Serv::stop() {
    try {
        beast::error_code ec;
        acceptor.close(ec);
        if (ec) throw runtime_error("Ошибка закрытия");
        ioContext.stop();
    }
    catch (const std::exception& e) {
        throw runtime_error("Ошибка закрытия сервера " + string(e.what()));
    }
}
