#pragma once
#include "Triangle.h"

//------------------Класс прямоугольный треугольник. Наследуем от треугольника-----------
class RightTriangle : public Triangle
{
public:
    RightTriangle(int a, int b, int c, int A, int B) : Triangle(a, b, c, A, B, 90)
    {
        name = "Прямоугольный треугольник";
    }
};
