#pragma once
#include "IsosTriangle.h"

//---------------------����� �������������� �����������. ��������� �� ��������������� ������������-------
class EquilTriangle : public IsosTriangle
{
public:
    EquilTriangle(int a) : IsosTriangle(a, a, a, 60, 60, 60)
    {
        name = "�������������� �����������";
    }
};