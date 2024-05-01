#include <Windows.h>
#include <iostream>
#include "IniParser.h"

int main() {
//	setlocale(LC_ALL, "rus");
	std::locale::global(std::locale("ru_RU.UTF-8"));    //да уж)))))))
	try {
		IniParser parser("test.ini");
		auto res1{ parser.get<std::wstring>(L"var2", L"Section2") };
		std::wcout << res1 << std::endl;
		auto res2{ parser.get<std::wstring>(L"var3", L"Section1") };
		std::wcout << res2;
	}
	catch (const std::runtime_error e) {
		std::cout << e.what();
	}
	catch(...){
		std::cout << "Отсутствует искомое значение";
	}
	return 0; 
}