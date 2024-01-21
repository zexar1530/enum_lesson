#pragma once

#include <iostream>
#include <string>
#include "Figure.h"
#include "Figure_Exception.h"

using namespace std;

//------------------Класс треугольник. Наследуем от фигуры-------------------
class Triangle : public Figure
{
protected:
    int a{}, b{}, c{};               //стороны фигуры
    int A{}, B{}, C{};               //углы фигуры

public:
    Triangle(int a, int b, int c, int A, int B, int C); //конструктор обычного треугольника

    void Print_Info() override;
};
