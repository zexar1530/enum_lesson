#include "RightQuadrangle.h"

RightQuadrangle::RightQuadrangle(int a, int b, int A) : Quadrangle(a, b, a, b, A, A, A, A)
{
    name = "�������������";
    if (!((a == c) && (b == d))) throw Figure_Exeption("������� a,c � b,d ������� �� ����� ");
}