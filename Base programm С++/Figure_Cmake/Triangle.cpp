#include "Triangle.h"

Triangle::Triangle(int a, int b, int c, int A, int B, int C) : a{ a }, b{ b }, c{ c }, A{ A }, B{ B }, C{ C } //����������� �������� ������������
{
    name = "�����������";
    side = 3;
    if((A + B + C) != 180)
        throw Figure_Exeption ("������ �������� ������. �������: ����� ����� �� ����� 180 ");
}

void Triangle::Print_Info()
{
    cout << name << ": " << endl;
    cout << "���������� ������: " << side << endl;
    cout << "�������: " << "a = " << a << " b = " << b << " c = " << c << endl;
    cout << "����: " << "A = " << A << " B = " << B << " C = " << C << endl << endl;
}