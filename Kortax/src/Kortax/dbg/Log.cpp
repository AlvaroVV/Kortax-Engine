#ifdef KT_PLATFORM_WINDOWS
#include <Windows.h>
#include <stdio.h>
#include "Log.h"

namespace kortax
{
	static const short int LOG_BUFFER_SIZE = 4096;
	static char sFormatBuffer[LOG_BUFFER_SIZE];

	void LogString(const char* aStr)
	{
		printf(aStr);
		printf("\n");

	}

	void LogFormatString(const char* aFmt, ...)
	{
		va_list lArgs;
		va_start(lArgs, aFmt);
		vsnprintf(sFormatBuffer, LOG_BUFFER_SIZE, aFmt, lArgs);

		LogString(sFormatBuffer);
		va_end(lArgs);
	}
}



#endif
