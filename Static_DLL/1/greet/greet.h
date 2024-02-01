#pragma once
#include <iostream>

using namespace std;

class Greet
{
public:
	explicit Greet(string);
	string GetName();
	
private:
	string name;
};
