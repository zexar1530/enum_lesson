#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

enum class Type {
    Warning,
    Error,
    FatalError,
    Unknown
};

class LogMessage {
private:
    Type type_msg;
    string text;

public:
    LogMessage(Type type, const string text) :type_msg(type), text(text) {}

    const Type type() const {
        return type_msg;
    }

    const string& message() const {
        return text;
    }
};

class LogHandler {
protected:
    LogHandler* next;

public:
    LogHandler(LogHandler* handler = nullptr) : next(handler) {};

    void setNext(LogHandler* handler) {
        if (handler) 
            next = handler;
    }

    virtual void handleMessage(LogMessage* message) = 0;
};

class Warning : public LogHandler {
public:
    void handleMessage(LogMessage* message) override {
        if (message->type() == Type::Warning) {
            cout << message->message();
        }
        else {
            if (next) {
                next->handleMessage(message);
            }
            else {
                throw runtime_error("No handler!");
            }
        }
    }
};

class Error : public LogHandler {
private:
    fstream file;

public:
    Error(const string& fname) {
        file.open(fname, fstream::app);
        if (!(file.is_open())) {
            throw runtime_error("Can't open file!");
        }
    }

    ~Error() {
        file.close();
    }

    void handleMessage(LogMessage* message) override {
        if (message->type() == Type::Error) {
            file << message->message();
        }
        else {
            if (next) {
                next->handleMessage(message);
            }
            else {
                throw runtime_error("No handler!");
            }
        }
    }
};

class FatalError : public LogHandler {
public:
    void handleMessage(LogMessage* message) override {
        if (message->type() == Type::FatalError) {
            throw std::runtime_error(message->message());
        }
        else {
            if (next) {
                next->handleMessage(message);
            }
            else {
                throw runtime_error("No handler!");
            }
        }
    }
};

class Unknown : public LogHandler {
public:
    void handleMessage(LogMessage* message) override {
        if (message->type() == Type::Unknown) {
            cout << message->message();
        }
        else {
            if (next) {
                next->handleMessage(message);
            }
            else {
                throw runtime_error("No handler!");
            }
        }
    }
};

int main() {
    vector<LogHandler*>log;
        LogMessage msg1(Type::Error, "Error\n");
        LogMessage msg2(Type::Warning, "Warning\n");
        LogMessage msg3(Type::Unknown, "Unknown message\n");
        LogMessage msg4(Type::FatalError, "Fatal error, programm closed\n");

        log.emplace_back(new FatalError());
        log.emplace_back(new Warning());
        log.emplace_back(new Unknown());
        log.emplace_back(new Error("file.txt"));

        for (size_t i{}; i < log.size()-1;i++) {
            log[i]->setNext(log[i + 1]);
        }

    try {
        log[2]->handleMessage(&msg1);
        log[0]->handleMessage(&msg2);
        log[0]->handleMessage(&msg3);
        log[0]->handleMessage(&msg4);
    }
    catch (std::exception& e) {
        cout << e.what() <<endl;
    }

    for (auto obj : log) {
        delete obj;
    }

    return 0;
}