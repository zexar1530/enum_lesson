#pragma once
#include <string>
#include <iostream>

class Transport
{
protected:
	virtual void Result() = 0;			//������� ������� �������
	int distanse{ 0 };				//���������
public:
	Transport() = delete;
	Transport(const std::string& name, int distanse);
	std::string name;					//�������� ������������� ��������
	double result_time{ 0 };			//����
	~Transport() = default;
};

