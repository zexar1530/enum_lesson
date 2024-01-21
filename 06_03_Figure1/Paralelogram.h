#pragma once
#include "Quadrangle.h"

//-----------------------класс паралелограмм. Наследуем от четырехугольника---------------------------------
class Paralelogram : public Quadrangle
{
public:
    Paralelogram(int a, int b, int A, int B) : Quadrangle(a, b, a, b, A, B, A, B)
    {
        if (!(a == c && b == d && A == C && B == D)) throw Figure_Exeption("Ошибка создания фигуры. Стороны и углы попарно не равны ");
        name = "Паралелограмм";
    }
};
