//--------------------------------Верблюд------------------------------


#pragma once								
#include "Transport.h"

class TrCamal : public Transport
{
protected:
	int driving_time{ 30 };			//время движения до отдыха
	int speed{ 10 };				//скорость
	int type_race{ 1 };					//тип гонки
private:
	inline static bool create{ false };		//статическая переменная (создан ли обьект)
public:
	TrCamal(const int distanse, const int type_race);
	void Result() override;			//функция расчета пробега
};

