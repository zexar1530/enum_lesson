#pragma once
#include "Transport.h"

class TrCamal : public Transport
{
protected:
	int driving_time{ 30 };			//����� �������� �� ������
	int speed{ 10 };				//��������
	int distanse{0};
private:
	inline static bool create{ false };		//����������� ���������� (������ �� ������)
public:
	TrCamal(int distanse, int type_race);
};

