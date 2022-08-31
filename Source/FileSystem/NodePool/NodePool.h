#pragma once

#include <FileSystem/Node.h>

#define NODEPOOL_MAX_SIZE 128

namespace MemoryFS
{
	class NodePool
	{
	public:
		static bool Init();
		static void Destroy();
		static Node* AllocateNode();
		static void DeallocateNode(NodeIndex index);
		static Node* GetNode(NodeIndex index);
		static Node* GetNodeFromParent(NodeIndex parent, const std::string& name);

		inline static Node* GetPool() { return s_Pool; }

	private:
		enum BlockType : uint8_t
		{
			BlockFree,
			BlockTaken
		};

	private:
		static Node* s_Pool;
		static uint8_t* s_Blocks;
		static NodeIndex s_LastFreedNode;
	};
}
