#include <iostream>
#include <vector>
#include "Transport.h"
#include "TrCamal.h"
#include "BroomStick.h"
#include "Magic_Car.h"
#include "Eagle.h"
#include "fastCamal.h"
#include "Boots.h"
#include "Cenyuar.h"
#include "Temp.h"

using namespace std;

void InputTypeRace(int&);	//ввод типа гонки
int RegistryTransport(const vector<Transport*>);	//регистрация транспорта
int PrintMenuChoise(int&, int&, const vector<Transport*>); //Вывод меню выбора транспорта

int main()
{
	setlocale(LC_ALL, "rus");
	vector<Transport*> transport;											//контейнер транспортных средств
	int tr{};																//тип гонки
	int distance{};															//расстояние
    cout << "Добро пожаловать в гоночный симулятор!\n";
	do
	{ 
		try																		//выходим если не верный тип
	{
		InputTypeRace(tr);
	}
		catch (runtime_error e)
	{
		cout << e.what();
		return 0;
	}
		cout << "Укажите длинну дистанции (должна быть положительна): ";
		cin >> distance;
		bool race{ true };
		while(race)
		{
			int i = 0;
			switch (RegistryTransport(transport))
			{
			case 1:
				//int i=0;								//вопрос решен, спасибо!
				do                                  
				{
					i = PrintMenuChoise(distance, tr, transport);
					switch (i)
					{
					case 1:
						try
						{
							transport.push_back(new Boots(distance, tr));
						}
						catch (const std::runtime_error& e)
						{
							cout << e.what();
						}
						break;
					case 2:
						try
						{
							transport.push_back(new BroomStick(distance, tr));
						}
						catch (const std::runtime_error& e)
						{
							cout << e.what();
						}
						break;
					case 6:
						try
						{
							transport.push_back(new fastCamal(distance, tr));
						}
						catch (const std::runtime_error& e)
						{
							cout << e.what();
						}
						break;
					case 5:
						try
						{
							transport.push_back(new Eagle(distance, tr));
						}
						catch (const std::runtime_error& e)
						{
							cout << e.what();
						}
						break;
					case 7: 
						try
						{
							transport.push_back(new Magic_Car(distance, tr));
						}
						catch (const std::runtime_error& e)
						{
							cout << e.what();
						}
						break;
					case 3:
						try
						{
							transport.push_back(new TrCamal(distance, tr));
						}
						catch (const std::runtime_error& e)
						{
							cout << e.what();
						}
						break;
					case 4:
						try
						{
							transport.push_back(new Cenyuar(distance, tr));
						}
						catch (const std::runtime_error& e)
						{
							cout << e.what();
						}
						break;
					case 0:
						break;
					}
				} while (i);
				break;
			case 2:
			{
				cout << "Результаты гонки:\n";
				for (int i{}; i < transport.size() - 1; i++)				//сравниваем и перестраиваем Vector
				{
					//Transport* t{new Transport { "",0 } }; временный обьект класса для замены невозможно создать так как он абстрактный
					Transport* t{ new Temp(0) };		//С абстракцией пришлось так. Может можно еще как что ббы для обмена не создавать временный класс?
					for (int j{}; j < transport.size() - 1; j++)
					{
						if (transport[j]->result_time > transport[j + 1]->result_time)
						{
							*t = *transport[j];
							*transport[j] = *transport[j + 1];
							*transport[j + 1] = *t;
						}
					}
				}
				int x = 0;
				for (const Transport* var : transport) cout << var->name << ": " << " Время: " << var->result_time << endl;
				cout << "1. Провести еще одну гонку\n";
				cout << "2. Выйти\n";
				cout << "Выберите дейтсвие ";
				//int x;								
				cin >> x;
				if (x == 2) return 0;
				transport.clear();						//очистка контейнера
				race = false;
				break;
			}
			default:
				break;
			}
		}
		
	} while (true);
	return 0;
}
void InputTypeRace(int& x)
{
	cout << "1. Гонка для наземного транспорта\n";
	cout << "2. Гонка для воздушщного транспорта\n";
	cout << "3. Гонка для наземного и воздушщного транспорта\n";
	cout << "Выберите тип гонки: ";
	cin >> x;
	system("Cls");
	if (x > 3 || x < 1) throw runtime_error("Нет такой гонки! До свидания.....");
}

int RegistryTransport(const vector<Transport*> t)
{
	if (t.empty())			//если вектор пустой то выводим первое меню
	{
		cout << "Должно быть зарегистрировано хотя бы 2 транспортных средства\n";
		int i{ 0 };			//выбор вида транспорта
		cout << "1. Зарегистрировать транспорт: ";
		cin >> i;
		system("Cls");
		return i;		//проверку на правильность ввода не делал))), доверяю что ввели 1
	}
	int i{ 0 };
	cout << "1. Зарегистрировать транспорт\n";		//если уже есть транспорт то 2 вид меню
	cout << "2. Начать гонку ";
	cin >> i;
	system("Cls");
	return i;
}

int PrintMenuChoise(int& dist, int& tr, const vector<Transport*> t)
{
	string tip_race;
	switch (tr)
	{
	case 1: tip_race = "Гонка для наземного транспорта "; break; 
	case 2: tip_race = "Гонка для воздушного транспорта "; break;
	case 3: tip_race = "Гонка для наземного и воздушного транспорта "; break;
	default: break;
	}
	cout << tip_race << "Расстояние: " << dist << endl;
	cout << "Зарегистрируемые транспортные средства: ";
	for (const Transport* var : t)
	{
		cout << var->name << " ";
	}
	cout << endl;
	cout << "1. Ботинки вездеходы\n";
	cout << "2. Метла\n";
	cout << "3. Верлюд\n";
	cout << "4. Кентавр\n";
	cout << "5. Орел\n";
	cout << "6. Верблюд-быстроход\n";
	cout << "7. Ковер-самолет\n";
	cout << "0. Закончить регистрацию\n";
	cout << "Выерите транспорт или 0 для окончания процесса регистрации: ";
	int i{};
	cin >> i;
	system("Cls");
	return i;
}

