#ifdef KT_PLATFORM_WINDOWS
#include <iostream>
#include "Log.h"

namespace Kortax
{
	void LogString(const char* aStr)
	{
		std::cout << aStr << "\n";
	}
}

#endif
