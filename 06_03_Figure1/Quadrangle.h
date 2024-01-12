#pragma once
#include <iostream>
#include <string>
#include "Figure.h"

using namespace std;
//-------------------------------Класс четырехугольник---------------------------------
class Quadrangle : public Figure
{
protected:
    int a{}, b{}, c{}, d{};               //стороны фигуры
    int A{}, B{}, C{}, D{};               //углы фигуры
public:
    Quadrangle(int a, int b, int c, int d, int A, int B, int C, int D) : a{ a }, b{ b }, c{ c }, d{ d }, A{ A }, B{ B }, C{ C }, D{ D } //конструктор обычного четырехугольника
    {
        name = "Четырехугольник";
        side = 4;
    }
    void Print_Info() override
    {
        cout << name << ": " << endl;
        cout << "Количество сторон: " << side << endl;
        cout << "Стороны: " << "a = " << a << " b = " << b << " c = " << c << " d = " << d << endl;
        cout << "Углы: " << "A = " << A << " B = " << B << " C = " << C << " D = " << D << endl << endl;
    };
};