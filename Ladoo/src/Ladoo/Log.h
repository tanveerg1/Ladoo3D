#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Ladoo {

	class LADOO_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core Log macros
#define LD_CORE_TRACE(...)   ::Ladoo::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LD_CORE_INFO(...)    ::Ladoo::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LD_CORE_ERROR(...)   ::Ladoo::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LD_CORE_WARN(...)    ::Ladoo::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LD_CORE_FATAL(...)   ::Ladoo::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define LD_TRACE(...)        ::Ladoo::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LD_INFO(...)         ::Ladoo::Log::GetClientLogger()->info(__VA_ARGS__)
#define LD_ERROR(...)        ::Ladoo::Log::GetClientLogger()->error(__VA_ARGS__)
#define LD_WARN(...)         ::Ladoo::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LD_FATAL(...)        ::Ladoo::Log::GetClientLogger()->fatal(__VA_ARGS__)