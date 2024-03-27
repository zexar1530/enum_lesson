#pragma once
#include <iostream>
#include <string>
#include "Figure.h"
#include "Figure_Exception.h"

using namespace std;
//-------------------------------����� ���������������---------------------------------
class Quadrangle : public Figure
{
protected:
    int a{}, b{}, c{}, d{};               //������� ������
    int A{}, B{}, C{}, D{};               //���� ������
public:
    Quadrangle(int a, int b, int c, int d, int A, int B, int C, int D) : a{ a }, b{ b }, c{ c }, d{ d }, A{ A }, B{ B }, C{ C }, D{ D } //����������� �������� ����������������
    {
        name = "���������������";
        side = 4;
        if (!((A + B + C + D) == 360)) throw Figure_Exeption("������ �������� ������. �������: ����� ����� �� ����� 360");
    }
    void Print_Info() override
    {
        cout << name << ": " << endl;
        cout << "���������� ������: " << side << endl;
        cout << "�������: " << "a = " << a << " b = " << b << " c = " << c << " d = " << d << endl;
        cout << "����: " << "A = " << A << " B = " << B << " C = " << C << " D = " << D << endl << endl;
    };
};