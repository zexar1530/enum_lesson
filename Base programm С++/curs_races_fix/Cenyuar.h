//---------------------------------Класс кентавр-------------------------------

#pragma once
#include "Transport.h"
class Cenyuar : public Transport
{
protected:
	int driving_time{ 8 };			//время движения до отдыха
	int speed{ 15 };				//скорость
	int type_race{ 1 };					//тип гонки
private:
	inline static bool create{ false };		//статическая переменная (создан ли обьект)
public:
	Cenyuar(const int distanse, const int type_race);
	void Result() override;
};

