#pragma once

#include <memory>

#ifdef LD_PLATFORM_WINDOWS
#if LD_DYNAMIC_LINK
	#ifdef LD_BUILD_DLL
		#define LADOO_API __declspec(dllexport)
	#else
		#define LADOO_API __declspec(dllimport)
	#endif 
#else
	#define LADOO_API
#endif
#else
	#error Have some ladoos!
#endif

#ifdef LD_DEBUG
	#define LD_ENABLE_ASSERTS
#endif // LD_DEBUG

#ifdef LD_ENABLE_ASSERTS
	#define LD_ASSERT(x, ...) { if(!(x)) { LD_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define LD_CORE_ASSERT(x, ...) { if(!(x)) { LD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define LD_ASSERT(x, ...)
	#define LD_CORE_ASSERT(x, ...)
#endif // LD_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define LD_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Ladoo {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}