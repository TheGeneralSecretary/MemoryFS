#include "buildpch.h"
#include "Util/Logger.h"

using namespace MemoryFS;

int main(int argc, char** argv)
{
	Logger::Init();
	LOGGER_DEBUG("MAIN");
	return 0;
}
