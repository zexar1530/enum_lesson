#include "TrCamal.h"

TrCamal::TrCamal(const int distanse, const int type_race) : Transport("�������", distanse)
{
	if (!((this->type_race == type_race) || (type_race == 3)))
		throw std::runtime_error("�������� ��� ������������� ��������!\n");
	if (create)	throw std::runtime_error("������� ��� ���������������!\n");
	create = true;
	Result();
}

void TrCamal::Result()
{
	int time = distanse / speed;			//����� ��� ���������
	int temp = time % driving_time;
	int rest = (time - temp) / driving_time;				//���������� ������� �� ���������
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
