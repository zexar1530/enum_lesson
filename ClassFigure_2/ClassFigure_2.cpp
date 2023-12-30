#include <iostream>

using namespace std;

class Triangle;
class Quadrangle;

void Print_Param(Triangle*);     // функция вывода на экран информации о треугольнике
void Print_Param(Quadrangle*);   // функция вывода на экран о четырехугольнике

struct ABCabc
{
    int a, b, c;    // стороны
    int A, B, C;    // углы
};

struct ABCDabcd
{
    int a, b, c, d, A, B, C, D; //стороны и углы четырехугольника
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
//-------------------------------четырехугольник------------------------------------------
class Quadrangle
{
private:
    ABCDabcd a_d{ 0 }; // наша структура для хранения данных треугольника
    string name_obj;

protected:
    void SetParamT(const int _a, const int _b, const int _c, const int _d, const int _A, const int _B = 90, const int _C = 90, const int _D = 90)
    {
        a_d.A = _A;     
        a_d.B = _B;
        a_d.C = _C;
        a_d.D = _D;
        a_d.a = _a;
        a_d.b = _b;
        a_d.c = _c;
        a_d.d = _d;
    }
    void SetParamT(const int _a, const int _A, const int _B, const int _D)  //перегрузка для ромба
    {
        a_d.A = _A;
        a_d.B = _B;
        a_d.C = _A;
        a_d.D = _D;
        a_d.a = _a;
        a_d.b = _a;
        a_d.c = _a;
        a_d.d = _a;
    }
    void SetParamT(const int _a)        // перегрузка для квадрата
    {
        a_d.A = 90;
        a_d.B = 90;
        a_d.C = 90;
        a_d.D = 90;
        a_d.a = _a;
        a_d.b = _a;
        a_d.c = _a;
        a_d.d = _a;
    }

public:
    Quadrangle() {};
    Quadrangle(const string name, const int _a, const int _b, const int _c, const int _d, const int _A, const int _B, const int _C, const int _D) //конструктор с параметрами
    {
        SetParamT(_a, _b, _c, _d, _A, _B, _C, _D);
        name_obj = name;
    }
    ABCDabcd GetParamT()  // геттер параметров четырехугольника
    {
        return a_d;
    }
    virtual string GetName() { return name_obj; };   // геттер названия фигуры
};
//---------------------------Параллелограмм---------------------------------------
class Par_Quadrangle : public Quadrangle
{
protected:
    string name_obj;
public:
    Par_Quadrangle(){};
    Par_Quadrangle(const string name, const int _a, const int _b, const int _c, const int _d, const int _A, const int _B, const int _C, const int _D) //конструктор с параметрами
    {
        SetParamT(_a, _b, _c, _d, _A, _B, _C, _D);
        name_obj = name;
    }
    virtual string GetName() { return name_obj; };   // геттер названия фигуры
};
//--------------------------Прямоугольник-----------------------------------------
class Pr_Quadrangle : public Quadrangle
{
private:
    string name_obj;
public:
    Pr_Quadrangle() {};
    Pr_Quadrangle(const string name, const int _a, const int _b, const int _c, const int _d, const int _A) //конструктор с параметрами
    {
        SetParamT(_a, _b, _c, _d, _A);
        name_obj = name;
    }
    virtual string GetName() { return name_obj; };   // геттер названия фигуры
};
//--------------------------Ромб--------------------------------------------------
class R_Quadrangle : public Par_Quadrangle
{
public:
    R_Quadrangle(const string name, const int _a, const int _A, const int _B, const int _C, const int _D) //конструктор с параметрами
    {
        SetParamT(_a, _A, _B, _D);
        name_obj = name;
    }
    virtual string GetName() { return name_obj; };   // геттер названия фигуры
};
//--------------------------Квадрат-----------------------------------------------
class K_Quadrangle : public Par_Quadrangle
{
public:
    K_Quadrangle(const string name, const int _a) //конструктор с параметрами
    {
        SetParamT(_a);
        name_obj = name;
    }
    virtual string GetName() { return name_obj; };
};

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

    Quadrangle q("Четырехугольник:\n", 10, 20, 30, 40, 50, 60, 70, 80);
    Print_Param(&q);

    Par_Quadrangle p("Паралелограмм:\n", 20, 30, 20, 30, 30, 40, 30, 40);
    Print_Param(&p);

    Pr_Quadrangle pr("Прямоугольник:\n", 10, 20, 10, 20, 90);
    Print_Param(&pr);

    R_Quadrangle ro("Ромб:\n", 30, 30, 40, 30, 40);
    Print_Param(&ro);

    K_Quadrangle k("Квадрат:\n", 20);
    Print_Param(&k);

    return 0;
}

void Print_Param(Triangle* p_data)
{
    ABCabc data_class = p_data->GetParamT();
    cout << p_data->GetName();
    cout << "Стороны: " << "a = " << data_class.a << " b = " << data_class.b << " c = " << data_class.c << endl;
    cout << "Углы: " << "A = " << data_class.A << " B = " << data_class.B << " C = " << data_class.C << endl << endl;
}

void Print_Param(Quadrangle* p_data)
{
    ABCDabcd data_class = p_data->GetParamT();
    cout << p_data->GetName();
    cout << "Стороны: " << "a = " << data_class.a << " b = " << data_class.b << " c = " << data_class.c << " d = " << data_class.d << endl;
    cout << "Углы: " << "A = " << data_class.A << " B = " << data_class.B << " C = " << data_class.C << " D = " << data_class.D << endl << endl;
}
