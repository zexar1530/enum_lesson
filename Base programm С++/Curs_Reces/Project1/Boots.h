//----------------------------������� ���������---------------------------


#pragma once
#include "Transport.h"
class Boots : public Transport
{
protected:
	int driving_time{ 60 };			//����� �������� �� ������
	int speed{ 6 };				//��������
	int type_race{ 1 };					//��� �����
private:
	inline static bool create{ false };		//����������� ���������� (������ �� ������)
public:
	Boots(const int distanse, const int type_race);
	void Result() override;			//������� ������� �������
};

