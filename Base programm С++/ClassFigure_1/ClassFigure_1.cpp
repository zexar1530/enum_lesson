
#include <iostream>
#include <string>
using namespace std;

class Figure
{
public:
    Figure(int count = 0)
    {
        sides_count = count;
        name_figure = "Фигура: ";
    };
    int Get_Sides_Count() { return sides_count; };  //метод возврата количества сторон
    string GetNameFigure() { return name_figure; }


protected:
    string name_figure; //имя фигуруры

private:
    int sides_count; //количество сторон
};

class Triangle : public Figure
{
public:
    Triangle() : Figure(3)
    {
        name_figure = "Треугольник: ";
    }
};

class Quadrangle : public Figure
{
public:
    Quadrangle() : Figure(4)
    {
        name_figure = "Четырехугольник: ";
    };
};



int main()
{
    setlocale (LC_ALL, "rus");
    cout << "количество сторон: \n";
    Figure f;
    cout << f.GetNameFigure() << f.Get_Sides_Count() << endl;
    Triangle t;
    cout << t.GetNameFigure() << t.Get_Sides_Count() << endl;
    Quadrangle q;
    cout << q.GetNameFigure() << q.Get_Sides_Count() << endl;
    return 0;
}

