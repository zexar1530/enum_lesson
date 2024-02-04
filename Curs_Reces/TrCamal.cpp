#include "TrCamal.h"

TrCamal::TrCamal(const int distanse, const int type_race) : Transport("Верблюд", distanse)
{
	if (!((this->type_race == type_race) || (type_race == 3)))
		throw std::runtime_error("Неверный тип транспортного средства!\n");
	if (create)	throw std::runtime_error("Верблюд уже зарегистрирован!\n");
	create = true;
	Result();
}

void TrCamal::Result()
{
	int time = distanse / speed;			//время без остановок
	int temp = time % driving_time;
	int rest = (time - temp) / driving_time;				//количество отдыхов на дистанции
	if (time >= driving_time)
	{
		for (int i{}; i < rest-1; i++)
		{
			if (i == 0) result_time = result_time + 5;
			else
				result_time = result_time + 8;
		}
		result_time = result_time + int(time);
	}
	else
		result_time = time;
}
