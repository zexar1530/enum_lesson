#include "TrCamal.h"

TrCamal::TrCamal(int distanse, int type_race) : Transport("�������", type_race)
{
	if (create)	throw std::runtime_error("������� ��� ���������������!\n");
	this->distanse = distanse;
	create = true;
}
