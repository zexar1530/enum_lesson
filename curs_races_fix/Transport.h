#pragma once
#include <string>
#include <iostream>

class Transport
{
protected:
	virtual void Result() = 0;			//функция расчета пробега
	int distanse{ 0 };				//дистанция
public:
	Transport(std::string name, int distanse);
	std::string name;					//Название транспортного средства
	double result_time{ 0 };			//итог
};

