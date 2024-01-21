#pragma once
#include "RightQuadrangle.h"

//-------------------------Класс квадрат. Наследуем от прямоугольника---------------------------------------
class Square : public RightQuadrangle
{
public:
    Square(int a) : RightQuadrangle(a, a, 90)
    {
        name = "Квадрат";
        if (!((a - b + c - d) == 0)) throw Figure_Exeption("все стороны не равны ");
    }
};
