//----------------------------класс верблюд быстроход------------------------


#pragma once
#include "Transport.h"
class fastCamal : public Transport
{
protected:
	int driving_time{ 10 };			//время движения до отдыха
	int speed{ 40 };				//скорость
	int type_race{ 1 };					//тип гонки
private:
	inline static bool create{ false };		//статическая переменная (создан ли обьект)
public:
	fastCamal(const int distanse, const int type_race);
	void Result() override;			//функция расчета пробега
};

