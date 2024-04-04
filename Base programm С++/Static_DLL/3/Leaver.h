#pragma once

#include <iostream>

//#ifdef DLLLIB_EXPORTS
//#define DLLLIB_API __declspec(dllexport)
//#else
//#define DLLLIB_API __declspec(dllimport)
//#endif


namespace Dynamic
{
	class Leaver
	{
	public:
		std::string GetName(std::string);

	};
}