#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//----------------------Класс фигуры----------------------------------------
class Figure
{
protected:
    string name;                          //имя фигуры
    int side{};                   //количество сторон
    virtual bool  Check()                            //проверка на правильность
    {
        if (side == 0) return true;
        return false;
    }
public:
    Figure(){};
    Figure(int a) : side{ 0 }
    {
        name = "Фигура";
    };
    virtual void Print_Info()                       //печать информации о фигуре
    {
        cout << name << ": " << endl;
        cout << "Количество сторон: " << side << endl;
        Check() ? cout << "Правильная" << endl << endl : cout << "Неправильная" << endl << endl;
    };
};
//------------------Класс треугольник. Наследуем от фигуры-------------------
class Triangle : public Figure
{
protected:
    int a{}, b{}, c{};               //стороны фигуры
    int A{}, B{}, C{};               //углы фигуры
    bool Check() override
    {
        if ((A + B + C) == 180) return 1;
        return 0;
    }
    void Print_Info() override
    {
        cout << name << ": " << endl;
        Check() ? cout << "Правильная" << endl : cout << "Неправильная" << endl;
        cout << "Количество сторон: " << side << endl;
        cout << "Стороны: " << "a = " << a << " b = " << b << " c = " << c << endl;
        cout << "Углы: " << "A = " << A << " B = " << B << " C = " << C << endl << endl;
    };
public:
    Triangle(int a, int b, int c, int A, int B, int C) : a{ a }, b{ b }, c{ c }, A{ A }, B{ B }, C{ C } //конструктор обычного треугольника
    {
        name = "Треугольник";
        side = 3;
    }
};
//------------------Класс прямоугольный треугольник. Наследуем от треугольника-----------
class RightTriangle : public Triangle
{
private:
    bool Check() override
    {
        if (!Triangle::Check()) return 0; //если не треугольник вообще то прекращаем проверки
        if (C == 90) return 1;
        return 0;
    }
public:
    RightTriangle(int a, int b, int c, int A, int B) : Triangle(a, b, c, A, B, 90)
    {
        name = "Прямоугольный треугольник";
    }
};
//--------------------Равнобедренный треугольник. Наследуем от треугольника------------
class IsosTriangle : public Triangle
{
private:
    bool Check() override
    {
        if (!Triangle::Check()) return 0;
        if ((C == A) && (a == c)) return 1;
        return 0;
    }
public:
    IsosTriangle(int a, int b, int c, int A, int B, int C) : Triangle(a, b, c, A, B, C)
    {
        name = "Равнобедренный треугольник";
    }
};
//---------------------Класс равносторонний треугольник. Наследуем от равностороннего треугольника-------
class EquilTriangle : public IsosTriangle
{
private:
    bool Check() override
    {
        if (!Triangle::Check()) return 0;
        if (c == b && a == c) return 1;
        return 0;
    }
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
    bool Check() override
    {
        if ((A + B + C + D) == 360) return 1;
        return 0;
    };
public:
    void Print_Info() override
    {
        cout << name << ": " << endl;
        Check() ? cout << "Правильная" << endl : cout << "Неправильная" << endl;
        cout << "Количество сторон: " << side << endl;
        cout << "Стороны: " << "a = " << a << " b = " << b << " c = " << c << " d = " << d << endl;
        cout << "Углы: " << "A = " << A << " B = " << B << " C = " << C << " D = " << D << endl << endl;
    };
public:
    Quadrangle(int a, int b, int c, int d, int A, int B, int C, int D) : a{ a }, b{ b }, c{ c }, d{ d }, A{A}, B{B}, C{C}, D{D} //конструктор обычного четырехугольника
    {
        name = "Четырехугольник";
        side = 4;
    }
};
//----------------------------Класс прямоугольник. Наследуем от четырехугольника---------------------------
class RightQuadrangle : public Quadrangle
{
private:
    bool Check() override
    {
        if (((A - B + C - D) == 0) && (a == c) && (b == d)) return 1;
        return 0;
    }
public:
    RightQuadrangle(int a, int b, int A) : Quadrangle(a, b, a, b, A, A, A, A)
    {
        name = "Прямоугольник";
    }
};
//-------------------------Класс квадрат. Наследуем от прямоугольника---------------------------------------
class Square : public RightQuadrangle
{
private:
    bool Check() override
    {
        if ((A == 90) && (C == 90) && (a == c) && (b == c)) return 1;
        return 0;
    }
public:
    Square(int a) : RightQuadrangle(a, a, 90)
    {
        name = "Квадрат";
    }
};
//-----------------------класс паралелограмм. Наследуем от четырехугольника---------------------------------
class Paralelogram : public Quadrangle
{
private:
    bool Check() override
    {
        if ((A == C) && (B == D) && (a == c) && (b == d) && (Quadrangle::Check())) return 1;
        return 0;
    }
public:
    Paralelogram(int a, int b, int A, int B) : Quadrangle(a, b, a, b, A, B, A, B)
    {
        name = "Паралелограмм";
    }
};
//-----------------------Класс ромб. Наследуем от паралелограмма.-------------------------------------------
class Rhombus : public Paralelogram
{
private:
    bool Check() override
    {
        if ((A == C) && (B == D) && (Quadrangle::Check())) return 1;
        return 0;
    }
public:
    Rhombus(int a, int A, int B) : Paralelogram(a, a, A, B)
    {
        name = "Ромб";
    }
};

int main()
{
    setlocale(LC_ALL, "rus");

    Figure *p_figure;                  //указатель на фигуру

    Figure figure(0);                    //обьект фигура
    figure.Print_Info();

    Triangle triangle(10, 20, 30, 50, 60, 70);  //создаем обьект треугольник
    p_figure = &triangle;
    p_figure->Print_Info();                          //печатаем информацию через родителя

    RightTriangle righttriagle(10, 20, 30, 50, 40); //прямоугольный
    p_figure = &righttriagle;
    p_figure->Print_Info();     

    IsosTriangle isostriangle(10, 20, 10, 50, 60, 50); //равнобедренный
    p_figure = &isostriangle;
    p_figure->Print_Info();

    EquilTriangle equiltriangle(30);                    //равносторонний
    p_figure = &equiltriangle;
    p_figure->Print_Info();

    Quadrangle quadrangle(10, 20, 30, 40, 50, 60, 70, 80);  //четырехугольник
    p_figure = &quadrangle;
    p_figure->Print_Info();

    RightQuadrangle rightquadrangle(10, 20, 90);        //прямоугольник
    p_figure = &rightquadrangle;
    p_figure->Print_Info();

    Square square(20);                                  //квадрат
    p_figure = &square;
    p_figure->Print_Info();

    Paralelogram paralelogram(20, 30, 30, 40);          //Паралелограм
    p_figure = &paralelogram;
    p_figure->Print_Info();

    Rhombus rhombus(30, 30, 40);                        //Ромб
    p_figure = &rhombus;
    p_figure->Print_Info();


    return 0;
}
