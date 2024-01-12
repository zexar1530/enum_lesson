#pragma once
#include "RightQuadrangle.h"

//-------------------------Класс квадрат. Наследуем от прямоугольника---------------------------------------
class Square : public RightQuadrangle
{
public:
    Square(int a) : RightQuadrangle(a, a, 90)
    {
        name = "Квадрат";
    }
};
