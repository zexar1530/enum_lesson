#pragma once
#include "Triangle.h"

//--------------------Равнобедренный треугольник. Наследуем от треугольника------------
class IsosTriangle : public Triangle
{
public:
    IsosTriangle(int a, int b, int c, int A, int B, int C) : Triangle(a, b, c, A, B, C)
    {
        if (!((a == c) && (A == C))) throw Figure_Exeption("Ошибка создания фигуры. Причина: стороны a и c не равны, углы A и C не равны ");
            name = "Равнобедренный треугольник";
    }
};