#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	try
	{
		auto test = Array<int>(4, 5);
		Array<int> arr(4, 4);
		test[0][0] = 4;
		arr = test;
		cout << test[0][0] << endl;
		cout << arr[0][0] << endl;
	}
	catch (const std::runtime_error& e)
	{
		cout << e.what();
	}

    return 0;
}
