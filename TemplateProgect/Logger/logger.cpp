#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const string& message) = 0;
};

class Console : public LogCommand {
public:
    void print(const string& message) override {
        cout << message << endl;
    }
};

class File : public LogCommand {
private:
    fstream file;
    const string fname;
public:
    File(const string& fname) :fname(fname) {
        file.open(fname, fstream::app);
        if (!file.is_open()) {
            throw runtime_error("Can't open file!");
        }
    }

    ~File() {
        file.close();
    }

    void print(const string& message) override {
        file << message << endl;
    }
};

void print(LogCommand& command, const string& message) {
    command.print(message);
}

int main() {
    Console console;
    File file("logger.txt");

    print(console, "Console");
    print(file, "File");

    return 0;
}