#pragma once
#include "IsosTriangle.h"

//---------------------Класс равносторонний треугольник. Наследуем от равностороннего треугольника-------
class EquilTriangle : public IsosTriangle
{
public:
    EquilTriangle(int a) : IsosTriangle(a, a, a, 60, 60, 60)
    {
        name = "Равносторонний треугольник";
    }
};