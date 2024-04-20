#include <memory>
#include <iostream>
#include <vector>

template<class T>
void move_vectors(std::vector<T>& one, std::vector<T>& two) {
	two = std::move(one);
//	two = one;
}

int main()
{
	std::vector <std::string> one = { "test_string1", "test_string2" };
	std::vector <std::string> two;
	move_vectors(one, two);
	for (auto v : two) std::cout << " " << v;
	for (auto v : one) std::cout << " " << v;		//С Move все работает!, а без просто копирование
	return 0;
}

