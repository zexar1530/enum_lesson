//----------------------------����� ������� ���������------------------------


#pragma once
#include "Transport.h"
class fastCamal : public Transport
{
protected:
	int driving_time{ 10 };			//����� �������� �� ������
	int speed{ 40 };				//��������
	int type_race{ 1 };					//��� �����
private:
	inline static bool create{ false };		//����������� ���������� (������ �� ������)
public:
	fastCamal(const int distanse, const int type_race);
	void Result() override;			//������� ������� �������
};

