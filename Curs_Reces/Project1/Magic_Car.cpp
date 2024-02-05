#include "Magic_Car.h"

Magic_Car::Magic_Car(const int distanse, const int type_race):Transport("Ковер-самолет", distanse)
{
	if (!((this->type_race == type_race) || (type_race == 3)))
		throw std::runtime_error("Неверный тип транспортного средства!\n");
	if (create)	throw std::runtime_error("Ковер-самолет уже зарегистрирован!\n");
	create = true;
	Result();
}

void Magic_Car::Result()
{
	if (speed == 0) throw std::runtime_error("Нулевая скорость!");
	if (distanse < 1000) result_time = distanse / speed;
	if ((distanse >= 1000) && (distanse < 5000)) result_time = (distanse * 0.97) / speed;
	if ((distanse >= 5000) && (distanse < 10000)) result_time = (distanse * 0.9) / speed;
	if (distanse >= 10000) result_time = (distanse * 0.95) / speed;
}
