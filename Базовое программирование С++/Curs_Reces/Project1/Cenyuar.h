//---------------------------------����� �������-------------------------------

#pragma once
#include "Transport.h"
class Cenyuar : public Transport
{
protected:
	int driving_time{ 8 };			//����� �������� �� ������
	int speed{ 15 };				//��������
	int type_race{ 1 };					//��� �����
private:
	inline static bool create{ false };		//����������� ���������� (������ �� ������)
public:
	Cenyuar(const int distanse, const int type_race);
	void Result() override;
};

