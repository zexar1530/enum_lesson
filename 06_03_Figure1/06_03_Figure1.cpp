//#include <iostream>   сразу возник вопрос, если я включаю библиотеки Iostream и string в
//#include <string>     заголовочных файлах классов то тут их включать необязательно?
#include "Figure.h"   // и еще если их включить то они вставятся несколько раз компилятором? 
#include "Rombus.h"   // если так то это увеличит размер исходного проекта?
#include "RightQuadrangle.h"
//#include "Triangle.h"
#include "Righttriangle.h"
//#include "IsosTriangle.h"
#include "Equil.h"
//#include "Paralelogram.h"
//#include "Quadrangle.h"
#include "Square.h"

using namespace std;


int main()
{
    setlocale(LC_ALL, "rus");

    Triangle triangle(10, 20, 30, 50, 60, 70);      //треугольник
    triangle.Print_Info();

    RightTriangle righttriagle(10, 20, 30, 50, 60); //прямоугольный
    righttriagle.Print_Info();

    IsosTriangle isostriangle(10, 20, 10, 50, 60, 50); //равнобедренный
    isostriangle.Print_Info();

    EquilTriangle equiltriangle(30);                    //равносторонний
    equiltriangle.Print_Info();

    Quadrangle quadrangle(10, 20, 30, 40, 50, 60, 70, 80);  //четырехугольник
    quadrangle.Print_Info();

    RightQuadrangle rightquadrangle(10, 20, 90);        //прямоугольник
    rightquadrangle.Print_Info();

    Square square(20);                                  //квадрат
    square.Print_Info();

    Paralelogram paralelogram(20, 30, 30, 40);          //Паралелограм
    paralelogram.Print_Info();

    Rhombus rhombus(30, 30, 40);                        //Ромб
    rhombus.Print_Info();

    return 0;
}
