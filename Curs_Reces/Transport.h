#pragma once
#include <string>
#include <iostream>

class Transport
{
protected:
	virtual void Result();			//функция расчета пробега
//	virtual void PrintResult() = 0;		//вывод результата на консоль
	int distanse{ 0 };				//дистанция
	int result_time{ 0 };			//итог
public:
	Transport(std::string name, int distanse);
	std::string name;					//Название транспортного средства
};

