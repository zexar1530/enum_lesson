
#include <iostream>
using namespace std;

struct Adress
{
    Adress(string town, string street, int n_house, short n_flat, int index)
        : town{ town }, street{ street }, n_house{ n_house }, n_flat{ n_flat }, index{ index }{}
    string  town;
    string  street;
    int     n_house;
    short   n_flat;
    int     index;
};

void Print_Struct(const Adress&);

int main()
{
    setlocale(LC_ALL, "rus");
    Adress adress1("Smolensk", "Ленина", 1, 1, 214000);
    Adress adress2("Москва", "Lenina", 1, 1, 100000);
    Print_Struct(adress1);
    Print_Struct(adress2);
    return 0;
}

void Print_Struct(const Adress &a)
{
    cout << "Город: " << a.town << endl;
    cout << "Улица: " << a.street << endl;
    cout << "Номер дома: " << a.n_house << endl;
    cout << "Номер квартиры: " << a.n_flat << endl;
    cout << "Индекс: " << a.index << endl;
    cout << "\n";
    return;
}
