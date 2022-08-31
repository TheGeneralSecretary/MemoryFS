#include "buildpch.h"
#include "Kernel/FUSE3/FUSE3Operations.h"

namespace MemoryFS
{
	std::shared_ptr<FileSystem> FUSE3Operations::s_FileSystem = nullptr;

	int FUSE3Operations::Init(const std::shared_ptr<FileSystem>& filesystem)
	{
		s_FileSystem = filesystem;
		return 1;
	}
	
	void FUSE3Operations::Destroy()
	{
	}

	int FUSE3Operations::GetAttr(const char* path, struct fuse_stat* stbuf, struct fuse3_file_info* fi)
	{
		const struct stat& st = s_FileSystem->GetAttr(path);
		stbuf->st_uid = st.st_uid;
		stbuf->st_gid = st.st_gid;
		stbuf->st_mode = st.st_mode;
		stbuf->st_nlink = st.st_nlink;
		stbuf->st_size = st.st_size;
		return 0;
	}

	int FUSE3Operations::ReadDir(const char* path, void* buf, fuse3_fill_dir_t filler, fuse_off_t off, struct fuse3_file_info* fi, enum fuse3_readdir_flags)
	{
		filler(buf, ".", NULL, 0, (fuse_fill_dir_flags)0);
		filler(buf, "..", NULL, 0, (fuse_fill_dir_flags)0);

		DNode dnode = s_FileSystem->ReadDir(path);
		for (NodeIndex i = 0; i < dnode.NodeCount; i++)
		{
			Node* node = s_FileSystem->GetNode(dnode.Nodes[i]);
			filler(buf, node->Data->Name.c_str(), NULL, 0, (fuse_fill_dir_flags)0);
		}

		return 0;
	}

	int FUSE3Operations::MkDir(const char* path, fuse_mode_t mode)
	{
		std::cout << "MAKING: " << path << std::endl;
		// FUSE 1 = ERROR
		return s_FileSystem->MkDir(path) ? 0 : 1;
	}
}
