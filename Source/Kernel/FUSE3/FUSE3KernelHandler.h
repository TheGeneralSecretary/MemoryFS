#pragma once

#include "Kernel/KernelHandler.h"
#include "FileSystem/FileSystem.h"

#include <memory>

namespace MemoryFS
{
	class FUSE3KernelHandler : public KernelHandler
	{
	public:
		virtual int Init(int argc, char** argv) override;
		virtual void Destroy() override;

	private:
		std::shared_ptr<FileSystem> m_FileSystem;
	};
}
