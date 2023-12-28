#include <iostream>

using namespace std;

class Triangle;

void Print_Param(Triangle*);     // функция вывода на экран информации о треугольнике

struct ABCabc
{
    int a, b, c;    // стороны
    int A, B, C;    // углы
};
//------------------------------треугольник--------------------------------------
class Triangle
{
private:
    ABCabc a_c{0}; // наша структура для хранения данных треугольника
    string name_obj;

protected:
    void SetParamT(const int _a, const int _b, const int _c, const int _A, const int _B, const int _C = 90)
    {
        a_c.A = _A;     // сеттер параметров треугольника
        a_c.B = _B;
        a_c.C = _C;
        a_c.a = _a;
        a_c.b = _b;
        a_c.c = _c;
    }
    void SetParamT(const int _a, const int _b)  //перегрузка для равностороннего
    {
        a_c.A = _b;     
        a_c.B = _b;
        a_c.C = _b;
        a_c.a = _a;
        a_c.b = _a;
        a_c.c = _a;
    }

public:
    Triangle() {};
    Triangle(const string name, const int _a, const int _b, const int _c, const int _A, const int _B, const int _C) //конструктор с параметрами
    {
        SetParamT(_a, _b, _c, _A, _B, _C);
        name_obj = name;
        if ((_a == _c) && (_A == _C)) name_obj = "Равнобедренный треугольник: \n"; // проверка на равнобедренный
    }
    ABCabc GetParamT()  // геттер параметров треугольника
    {
        return a_c;
    }
 virtual string GetName() { return name_obj; };   // геттер названия фигуры

};
//-----------------------------Прямоугольный треугольник---------------------------------
class L_Triangle : public Triangle
{
public:
    L_Triangle(string name, int a, int b, int c, int A, int B) : Triangle() //конструктор прямоугольного треугольника
    {
        SetParamT(a, b, c, A, B);
        name_obj = name;
    }
    string GetName() override { return name_obj; }     // наша виртуальная функция

private:
    string name_obj;        // имя фигуры
};
//------------------------------равносторонний треугольник------------------------------
class R_Triangle : public Triangle
{
public:
    R_Triangle(string name, int a, int b) : Triangle() //конструктор прямоугольного треугольника
    {
        SetParamT(a, b);
        name_obj = name;
    }
    string GetName() override { return name_obj; }     // наша виртуальная функция

private:
    string name_obj;        // имя фигуры
};
class Quadrangle;

int main()
{
    setlocale(LC_ALL, "rus");
    Triangle a("Треугольник:\n", 10, 20, 30, 50, 60, 70);
    Print_Param(&a);

    L_Triangle l("Прямоугольный треугольник: \n", 10, 20, 30, 50, 60);
    Print_Param(&l);            //тип не явно, так как дочерний оьект (а как будет через static_cast? не смог разобраться)

    a = Triangle("Треугольник:\n", 10, 20, 10, 50, 60, 50);   // не стал создавать дочерний класс, а сделал проверку на равнобедренность в конструкторе
    Print_Param(&a);

    R_Triangle r("Равносторонний треугольник: \n", 30, 60);
    Print_Param(&r);

    return 0;
}

void Print_Param(Triangle* p_data)
{
    ABCabc data_class = p_data->GetParamT();
    cout << p_data->GetName();
    cout << "Стороны: " << "a = " << data_class.a << " b = " << data_class.b << " c = " << data_class.c << endl;
    cout << "Углы: " << "A = " << data_class.A << " B = " << data_class.B << " C = " << data_class.C << endl << endl;
}
