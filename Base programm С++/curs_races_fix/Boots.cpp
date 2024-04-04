#include "Boots.h"

Boots::Boots(const int distanse, const int type_race):Transport("�������-���������", distanse)
{
	if (!((this->type_race == type_race) || (type_race == 3)))
		throw std::runtime_error("�������� ��� ������������� ��������!\n");
	if (create)	throw std::runtime_error("�������-��������� ��� ���������������!\n");
	create = true;
	Result();
}

void Boots::Result()
{
	if (speed==0) throw std::runtime_error("������� ��������!");
	double time = distanse / speed;			//����� ��� ���������
	int temp = (int)time % driving_time;
	double rest = time / driving_time;				//���������� ������� �� ���������
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
