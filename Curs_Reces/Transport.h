#pragma once
#include <string>
#include <iostream>

class Transport
{
protected:
	std::string name;					//�������� ������������� ��������
	int type_race{};					//��� �����
public:
	Transport(std::string name, int type_race);
};

