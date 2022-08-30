#include "buildpch.h"
#include "Kernel/FUSE3/FUSE3KernelHandler.h"
#include "Kernel/FUSE3/FUSE3Operations.h"

#include <fuse3/fuse.h>
#include "Kernel/FUSE3/Compat.h"

namespace MemoryFS
{
	static struct fuse_operations fops;

	int FUSE3KernelHandler::Init(int argc, char** argv)
	{
		fops.getattr = FUSE3Operations::GetAttr;
		fops.readdir = FUSE3Operations::ReadDir;

		return fuse_main(argc, argv, &fops, NULL);
	}

	void FUSE3KernelHandler::Destroy()
	{
	}
}
