#pragma once
#include <string>
#include <iostream>

class Transport
{
protected:
	virtual void Result();			//������� ������� �������
//	virtual void PrintResult() = 0;		//����� ���������� �� �������
	int distanse{ 0 };				//���������
	int result_time{ 0 };			//����
public:
	Transport(std::string name, int distanse);
	std::string name;					//�������� ������������� ��������
};

