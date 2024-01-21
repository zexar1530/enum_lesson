#include "Rombus.h"

Rhombus::Rhombus(int a, int A, int B) : Paralelogram(a, a, A, B)
{
    if (!((A==C) && (B==D) && ((a-b + c-d==0)))) throw Figure_Exeption("Ошибка создания фигуры. Все стороны и углы не равны ");
    name = "Ромб";
}