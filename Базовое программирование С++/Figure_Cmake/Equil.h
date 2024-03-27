#pragma once
#include "IsosTriangle.h"

//---------------------����� �������������� �����������. ��������� �� ��������������� ������������-------
class EquilTriangle : public IsosTriangle
{
public:
    EquilTriangle(int a) : IsosTriangle(a, a, a, 60, 60, 60)
    {
        if (!((A == B) && (b == c))) throw Figure_Exeption("������ �������� ������. �������: ��� ������� �� �����, ���� �� ����� 60 ");
        name = "�������������� �����������";
    }
};