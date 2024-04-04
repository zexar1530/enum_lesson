#include <iostream>
#include <string>
using namespace std;

//----------------------Класс фигуры Абстрактный----------------------------------------
class Figure
{
protected:
    string name;                          //имя фигуры
    int side{};                   //количество сторон
public:
    Figure() {};
    Figure(int a) : side{ 0 }
    {
        name = "Фигура";
    };
    virtual void Print_Info() = 0;                      //печать информации о фигуре
};
//------------------Класс треугольник. Наследуем от фигуры-------------------
class Triangle : public Figure
{
protected:
    int a{}, b{}, c{};               //стороны фигуры
    int A{}, B{}, C{};               //углы фигуры
    
public:
    Triangle(int a, int b, int c, int A, int B, int C) : a{ a }, b{ b }, c{ c }, A{ A }, B{ B }, C{ C } //конструктор обычного треугольника
    {
        name = "Треугольник";
        side = 3;
    }
    void Print_Info() override
    {
        cout << name << ": " << endl;
        cout << "Количество сторон: " << side << endl;
        cout << "Стороны: " << "a = " << a << " b = " << b << " c = " << c << endl;
        cout << "Углы: " << "A = " << A << " B = " << B << " C = " << C << endl << endl;
    };
};
//------------------Класс прямоугольный треугольник. Наследуем от треугольника-----------
class RightTriangle : public Triangle
{
public:
    RightTriangle(int a, int b, int c, int A, int B) : Triangle(a, b, c, A, B, 90)
    {
        name = "Прямоугольный треугольник";
    }
};
//--------------------Равнобедренный треугольник. Наследуем от треугольника------------
class IsosTriangle : public Triangle
{
public:
    IsosTriangle(int a, int b, int c, int A, int B, int C) : Triangle(a, b, c, A, B, C)
    {
        name = "Равнобедренный треугольник";
    }
};
//---------------------Класс равносторонний треугольник. Наследуем от равностороннего треугольника-------
class EquilTriangle : public IsosTriangle
{
public:
    EquilTriangle(int a) : IsosTriangle(a, a, a, 60, 60, 60)
    {
        name = "Равносторонний треугольник";
    }
};
//-------------------------------Класс четырехугольник---------------------------------
class Quadrangle : public Figure
{
protected:
    int a{}, b{}, c{}, d{};               //стороны фигуры
    int A{}, B{}, C{}, D{};               //углы фигуры
public:
    Quadrangle(int a, int b, int c, int d, int A, int B, int C, int D) : a{ a }, b{ b }, c{ c }, d{ d }, A{ A }, B{ B }, C{ C }, D{ D } //конструктор обычного четырехугольника
    {
        name = "Четырехугольник";
        side = 4;
    }
    void Print_Info() override
    {
        cout << name << ": " << endl;
        cout << "Количество сторон: " << side << endl;
        cout << "Стороны: " << "a = " << a << " b = " << b << " c = " << c << " d = " << d << endl;
        cout << "Углы: " << "A = " << A << " B = " << B << " C = " << C << " D = " << D << endl << endl;
    };
};
//----------------------------Класс прямоугольник. Наследуем от четырехугольника---------------------------
class RightQuadrangle : public Quadrangle
{
public:
    RightQuadrangle(int a, int b, int A) : Quadrangle(a, b, a, b, A, A, A, A)
    {
        name = "Прямоугольник";
    }
};
//-------------------------Класс квадрат. Наследуем от прямоугольника---------------------------------------
class Square : public RightQuadrangle
{
public:
    Square(int a) : RightQuadrangle(a, a, 90)
    {
        name = "Квадрат";
    }
};
//-----------------------класс паралелограмм. Наследуем от четырехугольника---------------------------------
class Paralelogram : public Quadrangle
{
public:
    Paralelogram(int a, int b, int A, int B) : Quadrangle(a, b, a, b, A, B, A, B)
    {
        name = "Паралелограмм";
    }
};
//-----------------------Класс ромб. Наследуем от паралелограмма.-------------------------------------------
class Rhombus : public Paralelogram
{
public:
    Rhombus(int a, int A, int B) : Paralelogram(a, a, A, B)
    {
        name = "Ромб";
    }
};

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