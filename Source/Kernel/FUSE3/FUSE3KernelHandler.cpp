#include "buildpch.h"
#include "Kernel/FUSE3/FUSE3KernelHandler.h"
#include "Kernel/FUSE3/FUSE3Operations.h"
#include "FileSystem/NodePool/NodePoolFileSystem.h"

#include <fuse3/fuse.h>
#include "Kernel/FUSE3/Compat.h"

namespace MemoryFS
{
	static struct fuse3_operations fops;

	int FUSE3KernelHandler::Init(int argc, char** argv)
	{
		m_FileSystem = std::make_shared<NodePoolFileSystem>();
		if (!m_FileSystem->Init()) return 0;
		m_FileSystem->MkFile("/file1");

		if (!FUSE3Operations::Init(m_FileSystem)) return 0;
		fops.getattr = FUSE3Operations::GetAttr;
		fops.readdir = FUSE3Operations::ReadDir;

		return fuse_main(argc, argv, &fops, NULL);
	}

	void FUSE3KernelHandler::Destroy()
	{
	}
}
