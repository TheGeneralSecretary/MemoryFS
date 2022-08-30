#pragma once

#include <fuse3/fuse.h>
#include <sys/stat.h>

namespace MemoryFS
{
	class FUSE3Operations
	{
	public:
		static int GetAttr(const char* path, struct fuse_stat* stbuf, struct fuse3_file_info* fi);
		static int ReadDir(const char* path, void* buf, fuse3_fill_dir_t filler, fuse_off_t off, struct fuse3_file_info* fi, enum fuse3_readdir_flags);
	};
}