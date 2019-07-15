#ifdef KT_PLATFORM_WINDOWS
#include <stdio.h>
#include <stdarg.h>
#include "Log.h"

namespace Kortax
{
	static const short int LOG_BUFFER_SIZE = 4096;
	static char sFormatBuffer[LOG_BUFFER_SIZE];

	void LogString(const char* aStr)
	{
		printf( aStr );
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
