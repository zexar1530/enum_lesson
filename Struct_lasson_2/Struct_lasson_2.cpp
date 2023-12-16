
#include <iostream>
using namespace std;

struct Bank
{
    int num;            // номер счета
    string name;        // имя 
    double balance;     // баланс счета
}bank;

void SetStructBank(Bank*, const double*); //функция приема и изменения баланса

int main()
{
    setlocale (LC_ALL, "rus");
    double new_balance; // переменная для передачи нового баланса

    cout << "Введите номер счета: ";
    cin >> bank.num;
    cout << "Введите имя владельца: ";
    cin >> bank.name;
    cout << "Введите баланс: ";
    cin >> bank.balance;
    
    cout << "Введите новый баланс: ";
    cin >> new_balance;

    SetStructBank(&bank, &new_balance); // меняем баланс

    // далее печатаем новую структуру и выходим

    cout << "Ваш счет: " << bank.name << ", " << bank.num << ", " << bank.balance << endl;
    return 0;
}

// наша маленькая функция

void SetStructBank(Bank *bank_f, const double *num_f )
{
    bank_f->balance = *num_f;
}
