#pragma once
#include "Triangle.h"

//------------------����� ������������� �����������. ��������� �� ������������-----------
class RightTriangle : public Triangle
{
public:
    RightTriangle(int a, int b, int c, int A, int B) : Triangle(a, b, c, A, B, 90)
    {
        if (C != 90) throw Figure_Exeption("������ �������� ������. �������: ���� � �� ����� 90: ");
        name = "������������� �����������";
    }
};
