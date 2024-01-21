#include "Triangle.h"

Triangle::Triangle(int a, int b, int c, int A, int B, int C) : a{ a }, b{ b }, c{ c }, A{ A }, B{ B }, C{ C } //конструктор обычного треугольника
{
    name = "Треугольник";
    side = 3;
    if((A + B + C) != 180)
        throw Figure_Exeption ("Ошибка создания фигуры. Причина: сумма углов не равна 180 ");
}

void Triangle::Print_Info()
{
    cout << name << ": " << endl;
    cout << "Количество сторон: " << side << endl;
    cout << "Стороны: " << "a = " << a << " b = " << b << " c = " << c << endl;
    cout << "Углы: " << "A = " << A << " B = " << B << " C = " << C << endl << endl;
}