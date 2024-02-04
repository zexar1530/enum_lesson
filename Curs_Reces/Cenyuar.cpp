#include "Cenyuar.h"

Cenyuar::Cenyuar(const int distanse, const int type_race) : Transport("Кентавр", distanse)
{
	if (!((this->type_race == type_race) || (type_race == 3)))
		throw std::runtime_error("Неверный тип транспортного средства!\n");
	if (create)	throw std::runtime_error("Кентавр уже зарегистрирован!\n");
	create = true;
	Result();					//сразу считаем результат
}

void Cenyuar::Result()
{
	double time = distanse / speed;			//время без остановок
	int temp = (int)time % driving_time;
	double rest = time / driving_time;				//количество отдыхов на дистанции
	if (time >= driving_time)
	{
		for (int i{}; i < rest - 1; i++)
		{
			result_time = result_time + 2;
		}
		result_time = result_time + time;
	}
	else
		result_time = time;
}
