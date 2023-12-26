#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Adress
{
public:
	Adress(string town, string street, int n_house, int n_flat) : town{ town }, street{ street }, n_house{ n_house }, n_flat{ n_flat } {}; //конструктор
	string OutAdress();	//вывод собранной строки для записи в файл
	string GetTown(); //геттер поля town

private:
	string town;	//название города
	string street;	//улица
	int n_house;	//номер дома
	int n_flat;		//номер квартиры
};

void SortAdress(Adress**, const int&); //функция сортировки


int main()
{
	setlocale(LC_ALL, "rus");

	int n{ 0 }; //количество адресов из файла
	ifstream in("in.txt"); // открываем для чтения
	in >> n; // читаем количество адресов
	Adress** adress = new Adress * [n]; //двучерный массив указателей
	for (int i{}; i < n; i++)
	{
		string town, street;
		int n_house{ 0 }, n_flat{ 0 };
		in >> town >> street >> n_house >> n_flat;
		*(adress + i) = new Adress{ town, street, n_house, n_flat }; // то же самое adress[i]
		//конструктор по умолчанию не использовал
		//Легких путей не ищем))))
	};
	in.close(); //закрываем файл

	// вызов функции сортировки
	SortAdress(adress, n);

	ofstream out("out.txt");	//создаем файл для записи
	out << n << "\n"; //пишем количество адресов
	for (int i{}; i < n; i++)
	{
		out << adress[i][0].OutAdress();	//пишем в файл
	}
	out.close(); //закрываем файл

	/*далее освобождаем память и выходим*/
	for (int i = 0; i < n; i++)
	{
		delete adress[i];
	}
	delete[] adress;
	return 0;
}

string Adress::OutAdress() // собственно клеим строки
{
	return town + ", " + street + ", " + to_string(n_house) + ", " + to_string(n_flat) + "\n";
}

string Adress::GetTown()
{
	return this->town;
}

void SortAdress(Adress** adr, const int& size)
{
	Adress temp_adress{ " ", " ", 0, 0 }; //экземпляр класса для сортировки
	for (int j = 0; j < size - 1; j++)
	{
		for (int i{}; i < size - 1; i++)
		{
			if (adr[i]->GetTown() > adr[i + 1]->GetTown())
			{
				//swap(adr[i], adr[i + 1]);  // так то же работает
				temp_adress = adr[i][0];
				adr[i][0] = adr[i + 1][0];
				adr[i + 1][0] = temp_adress;
			};
		}
	}
}
