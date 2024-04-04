//-------------------------------Класс ковер самолет-------------------------------


#pragma once
#include "Transport.h"

class Magic_Car : public Transport
{
protected:

	int speed{ 10 };				//скорость
	int type_race{ 2 };					//тип гонки
private:
	inline static bool create{ false };		//статическая переменная (создан ли обьект)
public:
	Magic_Car(const int distanse, const int type_race);
	void Result() override;
};

