#include "RightQuadrangle.h"

RightQuadrangle::RightQuadrangle(int a, int b, int A) : Quadrangle(a, b, a, b, A, A, A, A)
{
    name = "Прямоугольник";
    if (!((a == c) && (b == d))) throw Figure_Exeption("стороны a,c и b,d попарно не равны ");
}