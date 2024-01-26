#include <iostream>
#include <vector>

using namespace std;

enum TypeRace{Ground = 1, Aerial, Gr_aer} tr;
void InputTypeRace(int&);													//ввод типа гонки

int main()
{
	setlocale(LC_ALL, "rus");
	vector<Transport>* transport;											//контейнер транспортных средств
	int typerace{};															//тип гонки
	int distance{};															//расстояние
    cout << "Добро пожаловать в гоночный симулятор!\n";
	try																		//выходим если не верный тип
	{
		InputTypeRace(typerace);
	}
	catch (runtime_error e)
	{
		cout << e.what();
		return 0;
	}
	cout << "Укажите длинну дистанции (должна быть положительна): ";
	cin >> distance;
	cout << "Должно быть зарегистрировано хотя бы 2 транспортных средства\n";
	cout << "1. Зарегистрировать транспорт: ";
	cin >> ;

	
}
void InputTypeRace(int& x)
{
	cout << "1. Гонка для наземного транспорта\n";
	cout << "2. Гонка для воздушщного транспорта\n";
	cout << "3. Гонка для наземного и воздушщного транспорта\n";
	cout << "Выберите тип гонки: ";
	cin >> x;
	if (x > 3 || x < 1) throw runtime_error("Нет такой гонки! До свидания.....");
}

