#include "Header.h"         //подключаем header.h
#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    int a{}, b{};           //переменные
    char c;

    cout << "Введите первое число: ";
    cin >> a;
    cout << "Введите второе число: ";
    cin >> b;
    cout << "Выберите операцию (1 - сложение, 2 вычитание, 3 - умножение, 4 - деление, 5 - возведение в степень): ";
    cin >> c;

    switch (c)
    {
    case '1':
        Plus(&a, &b);
        break;
    case '2':
        Minus(&a, &b);
        break;
    case '3':
        Mul(&a, &b);
        break;
    case '4':
        Del(&a, &b);
        break;
    case '5':
        Mul_ab(&a, &b);
        break;
    default:
        break;
    }

    return 0;
}

