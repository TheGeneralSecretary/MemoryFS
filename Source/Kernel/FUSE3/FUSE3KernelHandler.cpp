#include "buildpch.h"
#include "Kernel/FUSE3/FUSE3KernelHandler.h"
#include "Kernel/FUSE3/FUSE3Operations.h"
#include "FileSystem/NodePool/NodePoolFileSystem.h"

#include <fuse3/fuse.h>
#include "Kernel/FUSE3/Compat.h"

/*
struct fuse3_operations
{
	int (*getattr)(const char* path, struct fuse_stat* stbuf,
	struct fuse3_file_info* fi);
	int (*readlink)(const char* path, char* buf, size_t size);
	int (*mknod)(const char* path, fuse_mode_t mode, fuse_dev_t dev);
	int (*mkdir)(const char* path, fuse_mode_t mode);
	int (*unlink)(const char* path);
	int (*rmdir)(const char* path);
	int (*symlink)(const char* dstpath, const char* srcpath);
	int (*rename)(const char* oldpath, const char* newpath, unsigned int flags);
	int (*link)(const char* srcpath, const char* dstpath);
	int (*chmod)(const char* path, fuse_mode_t mode,
	struct fuse3_file_info* fi);
	int (*chown)(const char* path, fuse_uid_t uid, fuse_gid_t gid, struct fuse3_file_info* fi);
	int (*truncate)(const char* path, fuse_off_t size, struct fuse3_file_info* fi);
	int (*open)(const char* path, struct fuse3_file_info* fi);
	int (*read)(const char* path, char* buf, size_t size, fuse_off_t off, struct fuse3_file_info* fi);
	int (*write)(const char* path, const char* buf, size_t size, fuse_off_t off, struct fuse3_file_info* fi);
	int (*statfs)(const char* path, struct fuse_statvfs* stbuf);
	int (*flush)(const char* path, struct fuse3_file_info* fi);
	int (*release)(const char* path, struct fuse3_file_info* fi);
	int (*fsync)(const char* path, int datasync, struct fuse3_file_info* fi);
	int (*setxattr)(const char* path, const char* name, const char* value, size_t size, int flags);
	int (*getxattr)(const char* path, const char* name, char* value, size_t size);
	int (*listxattr)(const char* path, char* namebuf, size_t size);
	int (*removexattr)(const char* path, const char* name);
	int (*opendir)(const char* path, struct fuse3_file_info* fi);
	int (*readdir)(const char* path, void* buf, fuse3_fill_dir_t filler, fuse_off_t off, struct fuse3_file_info* fi, enum fuse3_readdir_flags);
	int (*releasedir)(const char* path, struct fuse3_file_info* fi);
	int (*fsyncdir)(const char* path, int datasync, struct fuse3_file_info* fi);
	void* (*init)(struct fuse3_conn_info* conn, struct fuse3_config* conf);
	void (*destroy)(void* data);
	int (*access)(const char* path, int mask);
	int (*create)(const char* path, fuse_mode_t mode, struct fuse3_file_info* fi);
	int (*lock)(const char* path, struct fuse3_file_info* fi, int cmd, struct fuse_flock* lock);
	int (*utimens)(const char* path, const struct fuse_timespec tv[2], struct fuse3_file_info* fi);
	int (*bmap)(const char* path, size_t blocksize, uint64_t* idx);
	int (*ioctl)(const char* path, int cmd, void* arg, struct fuse3_file_info* fi, unsigned int flags, void* data);
	int (*poll)(const char* path, struct fuse3_file_info* fi, struct fuse3_pollhandle* ph, unsigned* reventsp);
	int (*write_buf)(const char* path, struct fuse3_bufvec* buf, fuse_off_t off, struct fuse3_file_info* fi);
	int (*read_buf)(const char* path, struct fuse3_bufvec** bufp, size_t size, fuse_off_t off, struct fuse3_file_info* fi);
	int (*flock)(const char* path, struct fuse3_file_info*, int op);
	int (*fallocate)(const char* path, int mode, fuse_off_t off, fuse_off_t len, struct fuse3_file_info* fi);
};
*/

namespace MemoryFS
{
	static struct fuse3_operations fops;

	int FUSE3KernelHandler::Init(int argc, char** argv)
	{
		m_FileSystem = std::make_shared<NodePoolFileSystem>();
		if (!m_FileSystem->Init()) return 0;

		//tmp
		m_FileSystem->MkFile("/file1");
		/*m_FileSystem->MkDir("/dir1");
		m_FileSystem->MkDir("/dir2");
		m_FileSystem->MkDir("/dir1/dir2");
		m_FileSystem->MkFile("/dir1/file2");
		m_FileSystem->MkFile("/dir1/dir2/file3");*/

		if (!FUSE3Operations::Init(m_FileSystem)) return 0;
		fops.getattr = FUSE3Operations::GetAttr;
		fops.readdir = FUSE3Operations::ReadDir;
		fops.mkdir = FUSE3Operations::MkDir;

		return fuse_main(argc, argv, &fops, NULL);
	}

	void FUSE3KernelHandler::Destroy()
	{
	}
}
