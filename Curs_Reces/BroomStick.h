//------------------------�����---------------------------

#pragma once
#include "Transport.h"

class BroomStick : public Transport
{
protected:
//	int driving_time{ 30 };			//����� �������� �� ������
	int speed{ 20 };				//��������
	int type_race{ 2 };					//��� �����
private:
	inline static bool create{ false };		//����������� ���������� (������ �� ������)
public:
	BroomStick (const int distanse, const int type_race);
	void Result() override;
};

