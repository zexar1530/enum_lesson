#pragma once
#include "IsosTriangle.h"

//---------------------Класс равносторонний треугольник. Наследуем от равностороннего треугольника-------
class EquilTriangle : public IsosTriangle
{
public:
    EquilTriangle(int a) : IsosTriangle(a, a, a, 60, 60, 60)
    {
        if (!((A == B) && (b == c))) throw Figure_Exeption("Ошибка создания фигуры. Причина: все стороны не равны, углы не равны 60 ");
        name = "Равносторонний треугольник";
    }
};