#include "buildpch.h"
#include "Kernel/FUSE3/FUSE3Operations.h"

#include <cstring>

namespace MemoryFS
{
	int FUSE3Operations::GetAttr(const char* path, struct fuse_stat* stbuf, struct fuse3_file_info* fi)
	{
		stbuf->st_uid = 0;
		stbuf->st_gid = 0;

		if (strcmp(path, "/") == 0)
		{
			stbuf->st_mode = S_IFDIR | 0755;
			stbuf->st_nlink = 2;
		}
		else
		{
			stbuf->st_mode = S_IFREG | 0644;
			stbuf->st_nlink = 1;
			stbuf->st_size = 1024;
		}

		return 0;
	}

	int FUSE3Operations::ReadDir(const char* path, void* buf, fuse3_fill_dir_t filler, fuse_off_t off, struct fuse3_file_info* fi, enum fuse3_readdir_flags)
	{
		filler(buf, ".", NULL, 0, (fuse_fill_dir_flags)0);
		filler(buf, "..", NULL, 0, (fuse_fill_dir_flags)0);

		if (strcmp(path, "/") == 0)
		{
			filler(buf, "file54", NULL, 0, (fuse_fill_dir_flags)0);
			filler(buf, "file349", NULL, 0, (fuse_fill_dir_flags)0);
		}

		return 0;
	}
}
