
#include "greet.h"


Greet::Greet(string name) :name{ name } {};

string Greet::GetName()
{
	return string("Здравствуйте, ") + name + string("!\n");
}



