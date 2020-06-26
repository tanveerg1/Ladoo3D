#pragma once

#ifdef LD_PLATFORM_WINDOWS
	#ifdef LD_BUILD_DLL
		#define LADOO_API __declspec(dllexport)
	#else
		#define LADOO_API __declspec(dllimport)
	#endif 
#else
	#error Have some ladoos!
#endif

#define BIT(x) (1 << x)