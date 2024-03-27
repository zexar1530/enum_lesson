//---------------------------------------Класс орел--------------------------

#pragma once
#include "Transport.h"
class Eagle : public Transport
{
protected:

	int speed{ 8 };				//скорость
	int type_race{ 2 };					//тип гонки
private:
	inline static bool create{ false };		//статическая переменная (создан ли обьект)
public:
	Eagle(const int distanse, const int type_race);
	void Result() override;
};

