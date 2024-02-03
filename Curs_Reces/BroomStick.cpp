#include "BroomStick.h"

BroomStick::BroomStick(const int distanse, const int type_race) : Transport("Метла", distanse)
{
	if (!((this->type_race == type_race) || (type_race == 3)))
		throw std::runtime_error("Неверный тип транспортного средства!\n");
	if (create)	throw std::runtime_error("Метла уже зарегистрирована!\n");
	create = true;
}

void BroomStick::Result()
{
}
