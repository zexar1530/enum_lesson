#pragma once
#include "RightQuadrangle.h"

//-------------------------����� �������. ��������� �� ��������������---------------------------------------
class Square : public RightQuadrangle
{
public:
    Square(int a) : RightQuadrangle(a, a, 90)
    {
        name = "�������";
        if (!((a - b + c - d) == 0)) throw Figure_Exeption("��� ������� �� ����� ");
    }
};
