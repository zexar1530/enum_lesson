#include <iostream>
#include <Windows.h>

using namespace std;

class Counter {
private:
    int count;

public:
    Counter() {
        this->count = 1;
    };

    Counter(int count) : count{ count } {};

    void Plus() { count++; };
    void Minus() { count--; };
    int ResultCounter() { return count; };
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");

    Counter* counter; // указатель на класс
    char command;
    string y_n;
    cout << "Хотите указать начальное значение счетчмка? Введите да или нет: ";
    cin >> y_n;
    // поленился делать проверку на нет))))), поэтому или ДА или дюая строка
    if (y_n == "да") {
        int i;
        cout << "Введите начальное значение счетчика: ";
        cin >> i;
        counter = new Counter(i); // если да то создаем оьект в памяти с установленным значением
    }
    else {
        counter = new Counter(); // если нет то конструктор по умолчанию
    }

    do
    {
        cout << "Введите команду('+', '-', '=' или 'x') : ";
        cin >> command;
        switch (command)
        {
        case '+': 
            counter->Plus();
            break;
        case '-': 
            counter->Minus();
            break;
        case '=': 
            cout << static_cast<int>(counter->ResultCounter()) << endl;
            break;
        case '*':
            cout << "До свидания!" << endl;
            delete counter; // освобождаем память
            return 0;
        default:
            cout << "Нет такой команды." << endl;
            break;
        }
    } while (true);

    return 0;
}
