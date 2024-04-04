#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Adress
{
public:
	Adress(string town, string street, int n_house, int n_flat) : town{town}, street{street}, n_house{n_house}, n_flat{n_flat}{}; //конструктор
	string OutAdress();	//вывод собранной строки для записи в файл

private:
	string town;	//название города
	string street;	//улица
	int n_house;	//номер дома
	int n_flat;		//номер квартиры
};




int main()
{
	setlocale(LC_ALL, "rus");
	int n{ 0 }; //количество адресов из файла
	ifstream in("in.txt"); // открываем для чтения
	in >> n; // читаем количество адресов
	Adress** adress = new Adress* [n];
	for (int i = 0; i < n; i++)
	{
		string town, street;
		int n_house{ 0 }, n_flat{ 0 };
		in >> town >> street >> n_house >> n_flat;
		adress[i] = new Adress(town, street, n_house, n_flat);
	}
	in.close(); //закрываем файл
	ofstream out("out.txt");	//создаем файл для записи
	out << n << "\n"; //пишем количество адресов
	for (int i = n - 1; i >= 0; i--)
	{
		out << adress[i]->OutAdress();	//пишем в файл в обратном порядке
	}
	out.close(); //закрываем файл
	/*далее освобождаем память и выходим
	выше обращался к методу класса через указатель,
	а можно было и так adress[i][0]*/
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

