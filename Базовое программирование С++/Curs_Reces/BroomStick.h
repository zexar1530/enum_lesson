//------------------------Метла---------------------------

#pragma once
#include "Transport.h"

class BroomStick : public Transport
{
protected:

	int speed{ 20 };				//скорость
	int type_race{ 2 };					//тип гонки
private:
	inline static bool create{ false };		//статическая переменная (создан ли обьект)
public:
	BroomStick (const int distanse, const int type_race);
	void Result() override;
};

