#include "Boots.h"

Boots::Boots(const int distanse, const int type_race):Transport("Ботинки-скороходы", distanse)
{
	if (!((this->type_race == type_race) || (type_race == 3)))
		throw std::runtime_error("Неверный тип транспортного средства!\n");
	if (create)	throw std::runtime_error("Ботинки-скороходы уже зарегистрирован!\n");
	create = true;
	Result();
}

void Boots::Result()
{
	if (speed==0) throw std::runtime_error("Нулевая скорость!");
	double time = distanse / speed;			//время без остановок
	int temp = (int)time % driving_time;
	double rest = time / driving_time;				//количество отдыхов на дистанции
	if (time >= driving_time)
	{
		for (int i{}; i < rest - 1; i++)
		{
			if (i == 0) result_time = result_time + 10;
			else
				result_time = result_time + 5;
		}
		result_time = result_time + time;
	}
	else
		result_time = time;
}
