#include "buildpch.h"
#include "Util/Logger.h"

#include <fuse3/fuse.h>
#include "Kernel/FUSE3/Compat.h"

using namespace MemoryFS;

struct fuse_operations fops;

int main(int argc, char** argv)
{
	Logger::Init();

	return fuse_main(argc, argv, &fops, NULL);
}
