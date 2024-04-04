#pragma once
#include "Triangle.h"

//------------------Класс прямоугольный треугольник. Наследуем от треугольника-----------
class RightTriangle : public Triangle
{
public:
    RightTriangle(int a, int b, int c, int A, int B) : Triangle(a, b, c, A, B, 90)
    {
        if (C != 90) throw Figure_Exeption("Ошибка создания фигуры. Причина: Угол С не равен 90: ");
        name = "Прямоугольный треугольник";
    }
};
