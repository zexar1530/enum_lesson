//-------------------------------����� ����� �������-------------------------------


#pragma once
#include "Transport.h"

class Magic_Car : public Transport
{
protected:

	int speed{ 10 };				//��������
	int type_race{ 2 };					//��� �����
private:
	inline static bool create{ false };		//����������� ���������� (������ �� ������)
public:
	Magic_Car(const int distanse, const int type_race);
	void Result() override;
};

