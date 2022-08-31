#include "buildpch.h"
#include "Kernel/FUSE3/FUSE3Operations.h"

#include <cstring>

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

	// finish reddir
	int FUSE3Operations::ReadDir(const char* path, void* buf, fuse3_fill_dir_t filler, fuse_off_t off, struct fuse3_file_info* fi, enum fuse3_readdir_flags)
	{
		filler(buf, ".", NULL, 0, (fuse_fill_dir_flags)0);
		filler(buf, "..", NULL, 0, (fuse_fill_dir_flags)0);

		if (strcmp(path, "/") == 0)
		{
			filler(buf, "file1", NULL, 0, (fuse_fill_dir_flags)0);
			filler(buf, "file2", NULL, 0, (fuse_fill_dir_flags)0);
		}

		return 0;
	}
}
