#include "TrCamal.h"

TrCamal::TrCamal(int distanse, int type_race) : Transport("Верблюд", type_race)
{
	if (create)	throw std::runtime_error("Верблюд уже зарегистрирован!\n");
	this->distanse = distanse;
	create = true;
}
