
#include <iostream>
#include "leaver.h"

using namespace std;
using namespace Dynamic;

int main()
{
    setlocale(LC_ALL, "rus");
    string name;
    cout << "Введите имя: ";
    cin >> name;
    Leaver l;
    cout << l.GetName(name);
    system("pause");
}

