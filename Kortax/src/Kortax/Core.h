#pragma once

#ifdef KT_PLATFORM_WINDOWS
	#ifdef KT_BUILD_DLL
		#define KORTAX_API __declspec(dllexport)
	#else
		#define KORTAX_API __declspec(dllimport)
	#endif
#else
	#error Kortax only supports Windows right now!
#endif
