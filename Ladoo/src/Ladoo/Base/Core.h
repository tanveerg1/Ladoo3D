#pragma once

#include <memory>

//Platform detection
#ifdef _WIN32
    /* Windows x86/x64*/
	#ifdef _WIN64
	    /* Windows x64 */
		#define LD_PLATFORM_WINDOWS
	#else
		#error "x86 Builds are not supported"
	#endif
#elif defined(__ANDROID__)
	#define LD_PLATFORM_ANDROID
	#error "Android not supported"
#elif defined(__linux__)
	#define LD_PLATFORM_LINUX
	#error "Linux not supported"
#else
	#error "Unknown Platform!"
#endif 
//End of platform detection

// DLL Support
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
// End of DLL support

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
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}