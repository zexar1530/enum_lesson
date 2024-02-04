#pragma once
#include "Transport.h"
class Temp : public Transport
{
private:
	void Result() override final
	{

	}
public:
	Temp(int d) :Transport("", 0)
	{
	};
	~Temp() {};
};

