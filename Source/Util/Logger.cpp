#include "buildpch.h"
#include "Util/Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace MemoryFS
{
	void Logger::Init(const std::string& name)
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_Logger = spdlog::stdout_color_mt(name);
		s_Logger->set_level(spdlog::level::trace);
	}
}
