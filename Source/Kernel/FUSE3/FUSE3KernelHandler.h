#pragma once

#include "Kernel/KernelHandler.h"

namespace MemoryFS
{
	class FUSE3KernelHandler : public KernelHandler
	{
	public:
		virtual int Init(int argc, char** argv) override;
		virtual void Destroy() override;
	};
}
