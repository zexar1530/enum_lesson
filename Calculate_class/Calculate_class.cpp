#include <iostream>

using namespace std;

class Calculate
{
private:
    double num1, num2;

public:
    bool set_num1(double num1) // функция сеттер
    {
        if (!num1) return 0; // если ноль то возрат false
        this->num1 = num1;  // устанавливаем значение поля и возращаем true
        return 1;
    };

    bool set_num2(double num2) // тоже самое но с полем num2
    {
        if (!num2) return 0; // если ноль то возрат false
        this->num2 = num2;  // устанавливаем значение поля и возращаем true
        return 1;
    };

    //далее идут арифметические функции
    double add() { return num1 + num2; };
    double multiply() { return num1 * num2; };
    double subtract_1_2() { return num2 - num1; };
    double subtract_2_1() { return num1 - num2; };
    double divide_1_2() { return num1 / num2; };
    double divide_2_1() { return num2 / num1; };
};
int main()
{
    setlocale(LC_ALL, "rus");
    double num{ 0 };
    Calculate cal; // экземпляр нашего класса
    for (; true;) {    //вечный цикл
        while (true) //вечный если вводить 0
        {
            cout << "Введите num1: ";
            cin >> num;
            if (cal.set_num1(num)) break;
            cout << "Неверный ввод!" << endl;
        };
        while (true) // то же если 0 то крутим
        {
            cout << "Введите num2: ";
            cin >> num;
            if (cal.set_num2(num)) break;
            cout << "Неверный ввод!" << endl;
        };
        // вызываем методы нашего класса
        cout << "num1 + num2 = " << cal.add() << endl;
        cout << "num1 - num2 = " << cal.subtract_1_2() << endl;
        cout << "num2 - num1 = " << cal.subtract_2_1() << endl;
        cout << "num1 * num2 = " << cal.multiply() << endl;
        cout << "num1 / num2 = " << cal.divide_1_2() << endl;
        cout << "num2 / num1 = " << cal.divide_2_1() << endl;
    };
    return 0;
}

   

