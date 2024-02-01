
#include <iostream>
#include "greet.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    string name;
    cout << "Введите имя: ";
    cin >> name;
    cout << Greet(name).GetName();
    system("pause");
}

