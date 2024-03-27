
#include "Leaver.h"
namespace Dynamic
{
	Leaver::Leaver(string name) :name{ name } {};

	string Leaver::GetName()
	{
		return string("До свидания, ") + name + string("!\n");
	}
}


