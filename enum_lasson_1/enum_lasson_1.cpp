
#include <iostream>

using namespace std;

// перечисление

enum class Mounth : short {
	January = 1, February, March, April, May, June, Jule, August, September, October, November, December
} mounth;

int main() {
	setlocale(LC_ALL, "rus");  // русский язык

	short in{ 0 };

	do{
		cout << "Введите номер месяца: ";
		cin >> in;

		switch (in)
		{case (static_cast<short>(Mounth::January)):
			cout << "Январь\n";
			break;
		case (static_cast<short>(Mounth::February)):
			cout << "Февраль\n";
			break;
		case (static_cast<short>(Mounth::March)):
			cout << "Март\n";
			break;
		case (static_cast<short>(Mounth::April)):
			cout << "Апрель\n";
			break;
		case (static_cast<short>(Mounth::May)):
			cout << "Май\n";
			break;
		case (static_cast<short>(Mounth::June)):
			cout << "Июнь\n";
			break;
		case (static_cast<short>(Mounth::Jule)):
			cout << "Июль\n";
			break;
		case (static_cast<short>(Mounth::August)):
			cout << "Август\n";
			break;
		case (static_cast<short>(Mounth::September)):
			cout << "Сентябрь\n";
			break;
		case (static_cast<short>(Mounth::October)):
			cout << "Октябрь\n";
			break;
		case (static_cast<short>(Mounth::November)):
			cout << "Ноябрь\n";
			break;
		case (static_cast<short>(Mounth::December)):
			cout << "Декарь\n";
			break;
		default:
			if (in < 0 || in >= 13) cout << "Неправильный номер!\n";
			break;
		}

	} while (in);

	cout << "До свидания\n";
	return 0;
}