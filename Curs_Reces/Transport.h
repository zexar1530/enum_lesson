#pragma once
#include <string>
#include <iostream>

class Transport
{
protected:
	std::string name;					//Ќазвание транспортного средства
	int type_race{};					//тип гонки
public:
	Transport(std::string name, int type_race);
};

