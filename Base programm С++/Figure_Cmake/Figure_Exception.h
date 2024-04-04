#pragma once

#include <iostream>

using namespace std;


class Figure_Exeption : public exception
{
private:
	const char* message;
public:
	Figure_Exeption(const char* message) :message{ message } {}
	const char* what() const override
	{
		return message;
	}
};
