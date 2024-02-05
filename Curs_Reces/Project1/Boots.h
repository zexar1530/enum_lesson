//----------------------------Ботинки вездеходы---------------------------


#pragma once
#include "Transport.h"
class Boots : public Transport
{
protected:
	int driving_time{ 60 };			//время движения до отдыха
	int speed{ 6 };				//скорость
	int type_race{ 1 };					//тип гонки
private:
	inline static bool create{ false };		//статическая переменная (создан ли обьект)
public:
	Boots(const int distanse, const int type_race);
	void Result() override;			//функция расчета пробега
};

