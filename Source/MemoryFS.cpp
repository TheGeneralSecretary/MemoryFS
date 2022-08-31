#include "buildpch.h"
#include "Util/Logger.h"
#include "Kernel/FUSE3/FUSE3KernelHandler.h"

//#include "FileSystem/NodePool/NodePoolFileSystem.h"

using namespace MemoryFS;

int main(int argc, char** argv)
{
	Logger::Init();

	FUSE3KernelHandler fshandler;
	return fshandler.Init(argc, argv);

	/*
	NodePoolFileSystem filesystem;
	filesystem.Init();
	filesystem.MkFile("/file1");
	filesystem.MkDir("/dir1");
	filesystem.MkDir("/dir2");
	filesystem.MkDir("/dir1/dir2");
	filesystem.MkFile("/dir1/file2");
	filesystem.MkFile("/dir1/dir2/file3");

	//filesystem.PrintTest();

	DNode dnode;
	dnode = filesystem.ReadDir("/dir1");
	if (dnode.NodeCount > 0)
	{
		for (int i = 0; i < dnode.NodeCount; i++)
		{
			std::cout << filesystem.GetNode(dnode.Nodes[i])->Data->Name << std::endl;
		}
	}
	else
	{
		LOGGER_DEBUG("NO NODES READDIR");
	}

	return 0;*/
}
