#include "Eagle.h"

Eagle::Eagle(const int distanse, const int type_race): Transport("Орел", distanse)
{
	if (!((this->type_race == type_race) || (type_race == 3)))
		throw std::runtime_error("Неверный тип транспортного средства!\n");
	if (create)	throw std::runtime_error("Орел уже зарегистрирован!\n");
	create = true;
	Result();
}

void Eagle::Result()
{
	result_time = (distanse * 0.94) / speed;
}
