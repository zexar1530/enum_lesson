#include "Start.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int main() {

    locale::global(locale("Russian"));
    setlocale(LC_ALL, "Russian");

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    try {
        Start a("Config.ini");
        a.run();
        return 0;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}