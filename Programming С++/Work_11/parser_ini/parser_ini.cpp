#include <Windows.h>
#include <iostream>
#include "IniParser.h"

int main() {
	setlocale(LC_ALL, "rus");
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	try {
		IniParser parser("test.ini");
		auto res1{ parser.get<std::string>("var2", "Section2") };
		auto res2{ parser.get<int>("var1", "Section2") };
		std::cout << res1 << std::endl;
		std::cout << res2;
	}
	catch (const std::runtime_error e) {
		std::cout << e.what();
	}
	catch(...){
		std::cout << "______________________________";
	}
	return 0; 
}