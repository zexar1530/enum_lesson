#pragma once
#include "Transport.h"

class TrCamal : public Transport
{
protected:
	int driving_time{ 30 };			//время движения до отдыха
	int speed{ 10 };				//скорость
	int distanse{0};
private:
	inline static bool create{ false };		//статическая переменная (создан ли обьект)
public:
	TrCamal(int distanse, int type_race);
};

