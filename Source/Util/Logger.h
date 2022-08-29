#pragma once

#include <spdlog/spdlog.h>
#include <string>

namespace MemoryFS
{
	class Logger
	{
	public:
		static void Init(const std::string& name = "Logger");
		inline static std::shared_ptr<spdlog::logger> GetLogger()
		{
			return s_Logger;
		}

	private:
		inline static std::shared_ptr<spdlog::logger> s_Logger;
	};
}

#define LOGGER_INFO(...)	MemoryFS::Logger::GetLogger()->info(__VA_ARGS__)
#define LOGGER_WARN(...)	MemoryFS::Logger::GetLogger()->warn(__VA_ARGS__)
#ifdef BUILD_DEBUG
#define LOGGER_DEBUG(...)	MemoryFS::Logger::GetLogger()->debug(__VA_ARGS__)
#else
#define LOGGER_DEBUG(...)
#endif
#define LOGGER_ERROR(...)	MemoryFS::Logger::GetLogger()->error(__VA_ARGS__)
#define LOGGER_CRITICAL(...)MemoryFS::Logger::GetLogger()->critical(__VA_ARGS__)
#define LOGGER_TRACE(...)	MemoryFS::Logger::GetLogger()->trace(__VA_ARGS__)
