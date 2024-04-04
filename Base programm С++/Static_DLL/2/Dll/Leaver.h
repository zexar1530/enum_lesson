#pragma once
#include <iostream>

#ifdef DLL_EXPORTS
#define DLL_API __declspec (dllexport)
#else
#define DLL_API __declspec (dllimport)
#endif


using namespace std;

namespace Dynamic
{
	class DLL_API Leaver
	{
	public:
		inline explicit Leaver(string);
		string GetName();

	private:
		string name;
	};
}