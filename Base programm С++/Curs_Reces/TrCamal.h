//--------------------------------�������------------------------------


#pragma once								
#include "Transport.h"

class TrCamal : public Transport
{
protected:
	int driving_time{ 30 };			//����� �������� �� ������
	int speed{ 10 };				//��������
	int type_race{ 1 };					//��� �����
private:
	inline static bool create{ false };		//����������� ���������� (������ �� ������)
public:
	TrCamal(const int distanse, const int type_race);
	void Result() override;			//������� ������� �������
};

