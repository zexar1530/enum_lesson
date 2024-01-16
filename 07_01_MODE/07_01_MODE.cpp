#include <iostream>
#define MODE 1
#define SUB(a, b) ((a)-(b))

#if MODE == 1
const void add(int &a, int &b) {
	std::cout << "Result addition: " << a + b << std::endl;
	}
#endif // MODE == 1


int main()
{
	setlocale(LC_ALL, "rus");

#ifndef MODE
#error Необходимо определить MODE;
#endif // !MODE

#if MODE == 0
	std::cout << "Работаю в режиме тренировки!" << std::endl;
#elif MODE == 1
	int x{}, y{};
	std::cout << "Работаю в боевом режиме" << std::endl;
	std::cout << "Input number 1: ";
	std::cin >> x;
	std::cout << "Input number 2: ";
	std::cin >> y;
	add(x, y);
#else
	std::cout << "Неизвестный режим. Завершение работы" << std::endl;
#endif // MODE

	std::cout << std::endl;
	int a = 6;
	int b = 5;
	int c = 2;
	std::cout << SUB(a, b) << std::endl;
	std::cout << SUB(a, b) * c << std::endl;
	std::cout << SUB(a, b + c) * c << std::endl;

}

