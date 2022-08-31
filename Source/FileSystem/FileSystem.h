#pragma once

#include <string>
#include <sys/stat.h>

namespace MemoryFS
{
	class FileSystem
	{
	public:
		virtual bool Init() = 0;
		virtual void Destroy() = 0;
		virtual bool MkFile(const std::string& path) = 0;
		virtual const struct stat& GetAttr(const std::string& path) = 0;
	};
}
