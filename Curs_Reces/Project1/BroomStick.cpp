#include "BroomStick.h"

BroomStick::BroomStick(const int distanse, const int type_race) : Transport("�����", distanse)
{
	if (!((this->type_race == type_race) || (type_race == 3)))
		throw std::runtime_error("�������� ��� ������������� ��������!\n");
	if (create)	throw std::runtime_error("����� ��� ����������������!\n");
	create = true;
	Result();
}

void BroomStick::Result()
{
	if (speed==0) throw std::runtime_error("������� ��������!");
	int temp = distanse - (distanse % 1000);
	int koff{};
	for (int i{}; i < temp / 1000; i++) koff += 1;
	distanse = distanse - (distanse * koff / 100);
	result_time = distanse / speed;
}
