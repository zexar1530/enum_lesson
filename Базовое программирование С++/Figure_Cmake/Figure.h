#pragma once
#include <string>

//----------------------Класс фигуры Абстрактный----------------------------------------
class Figure
{
protected:
    std::string name;                          //имя фигуры
    int side{};                   //количество сторон
public:
    Figure();
    Figure(int a);
    virtual void Print_Info() = 0;                      //печать информации о фигуре
};
