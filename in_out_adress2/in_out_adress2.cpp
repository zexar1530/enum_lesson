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
	Adress** adress = new Adress* [n]; //массив указателей на класс
	for (int i = 0; i < n; i++)
	{
		string town, street;
		int n_house{ 0 }, n_flat{ 0 };
		in >> town >> street >> n_house >> n_flat;
		adress[i] = new Adress(town, street, n_house, n_flat); //инициализируем элементы при создании указателей
	}
	in.close(); //закрываем файл

	// вызов функции сортировки
	SortAdress(adress, n);

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

string Adress::GetTown()
{
	return this->town;
}

void SortAdress(Adress **adr, const int &size)
{
	Adress **temp_adress = new Adress* [0]; //экземпляр класса для сортировки
	temp_adress[0] = new Adress(" ", " ", 0, 0);
	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < size - 1; i++)
		{
			if (adr[i]->GetTown() < adr[i + 1]->GetTown())
			{

				temp_adress[0][0] = adr[i][0];              //программа рабботает и сортирует, но при условии нажать пропаустить исключение
				adr[i][0] = adr[i + 1][0];					//почему оно выскакивает, немогу сообразить, на отладчике гонял, по адресам вроде нормально все
				adr[i + 1][0] = temp_adress[0][0];			//не хотел делать банально замены через методы класса. заморочился с заменой адресации в массиве обьектов
			};												//через Vector можно просто сделать! 
		}													// можно не делать было двойной массив, но тогда никак не проинициализировать обьекты, так как условие
	}														// задачи конструктор с параметрами
	delete temp_adress[0];									// Пожалуйста обьясните, где тут может ошибка быть зарыта
	delete[] temp_adress;
}

