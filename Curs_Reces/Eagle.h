//---------------------------------------����� ����--------------------------

#pragma once
#include "Transport.h"
class Eagle : public Transport
{
protected:

	int speed{ 8 };				//��������
	int type_race{ 2 };					//��� �����
private:
	inline static bool create{ false };		//����������� ���������� (������ �� ������)
public:
	Eagle(const int distanse, const int type_race);
	void Result() override;
};

