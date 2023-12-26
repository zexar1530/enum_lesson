
#include <iostream>
using namespace std;

class Figure
{
public:
    Figure(int count = 0)
    {
        sides_count = count;
        name_figure = "Фигура: ";
        if (count == 0) cout << name_figure << sides_count << endl;
    };
    int Get_Sides_Count() { return sides_count; };  //метод возврата количества сторон

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
        cout << name_figure << Get_Sides_Count() << endl;
    }
};

class Quadrangle : public Figure
{
public:
    Quadrangle() : Figure(4)
    {
        name_figure = "Четырехугольник: ";
        cout << name_figure << Get_Sides_Count() << endl;
    };
};



int main()
{
    setlocale (LC_ALL, "rus");
    cout << "количество сторон: \n";
    Figure f;
    Triangle t;
    Quadrangle q;
    return 0;
}

