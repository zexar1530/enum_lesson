#pragma once
#include "Triangle.h"

//--------------------Равнобедренный треугольник. Наследуем от треугольника------------
class IsosTriangle : public Triangle
{
public:
    IsosTriangle(int a, int b, int c, int A, int B, int C) : Triangle(a, b, c, A, B, C)
    {
        name = "Равнобедренный треугольник";
    }
};