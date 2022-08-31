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

	/*NodePoolFileSystem filesystem;
	filesystem.Init();
	filesystem.MkFile("/file1");

	filesystem.PrintTest();*/
	//return 0;
}
