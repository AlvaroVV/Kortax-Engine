#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "../Core.h"

namespace Kortax
{
	//Print a string
	KORTAX_API void  LogString(const char* aStr);

	KORTAX_API void  LogFormatString(const char* aFmt, ...);

};

class MyLog
{
public:
	void test() { printf("TEST"); }
};