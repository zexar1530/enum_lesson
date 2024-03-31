
#include <iostream>
#include "smart_array.h"

int main()
{
    setlocale(LC_ALL, "rus");

	try {
		smart_array arr(5);
		arr.add_element(1);
		arr.add_element(4);
		arr.add_element(155);
		arr.add_element(14);
		arr.add_element(15);
		arr.add_element(25);
		std::cout << arr.get_element(1) << std::endl;
		std::cout << arr.get_element(5) << std::endl;

		smart_array new_array(2);
		new_array.add_element(44);
		new_array.add_element(34);

		arr = new_array;
		std::cout << new_array.get_element(1) << std::endl;
		std::cout << arr.get_element(1) << std::endl;

		smart_array move_arr(std::move(arr));
		std::cout << move_arr.get_element(0) << std::endl;


	}
	catch (const std::runtime_error& ex) {
		std::cout << ex.what() << std::endl;
	}
}

