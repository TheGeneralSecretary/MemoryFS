#pragma once

namespace MemoryFS
{
	class KernelHandler
	{
	public:
		virtual int Init(int argc, char** argv) = 0;
		virtual void Destroy() = 0;
	};
}
