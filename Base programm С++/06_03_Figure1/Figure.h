#pragma once
#include <string>

//----------------------����� ������ �����������----------------------------------------
class Figure
{
protected:
    std::string name;                          //��� ������
    int side{};                   //���������� ������
public:
    Figure();
    Figure(int a);
    virtual void Print_Info() = 0;                      //������ ���������� � ������
};
