#include "buildpch.h"
#include "FileSystem/NodePool/NodePool.h"
#include "Util/Logger.h"

namespace MemoryFS
{
	Node* NodePool::s_Pool = nullptr;
	uint8_t* NodePool::s_Blocks = nullptr;
	NodeIndex NodePool::s_LastFreedNode = -1;

	bool NodePool::Init()
	{
		s_Blocks = new uint8_t[NODEPOOL_MAX_SIZE];
		if (!s_Blocks) return false;
		memset(s_Blocks, 0, NODEPOOL_MAX_SIZE);

		s_Pool = new Node[NODEPOOL_MAX_SIZE];
		if (!s_Pool) return false;

		Node* root = NodePool::AllocateNode();
		if (!root)
		{
			LOGGER_DEBUG("Failed to Allocate Root");
			return false;
		}

		root->Parent = -1;
		root->Type = NodeType::DIRECTORY;
		root->Data = CreateNodeData("/");
		root->Children = new NodeChildren;
		InitializeNodeStat(root);

		LOGGER_DEBUG("Initialized NodePool");
		return true;
	}

	void NodePool::Destroy()
	{
		s_LastFreedNode = -1;

		for (NodeIndex i = 0; i < NODEPOOL_MAX_SIZE; i++)
		{
			if (s_Blocks[i] == BlockType::BlockTaken)
			{
				Node* node = GetNode(i);
				if (node->Data)
					delete node->Data; // sp?
			}
		}

		if (s_Pool)
			delete s_Pool;
		if (s_Blocks)
			delete s_Blocks;

		LOGGER_DEBUG("Destroyed NodePool");
	}

	Node* NodePool::AllocateNode()
	{
		NodeIndex i = 0;
		if (s_LastFreedNode != -1)
		{
			LOGGER_DEBUG("Using Last Freed Node: {}", s_LastFreedNode);
			i = s_LastFreedNode;
			s_LastFreedNode = -1;
			goto _ALLOC;
		}
		
		for (i; i < NODEPOOL_MAX_SIZE; i++)
		{
			if (s_Blocks[i] == BlockType::BlockFree)
			{
			_ALLOC:
				s_Blocks[i] = BlockType::BlockTaken;
				Node* node = GetNode(i);
				node->Index = i;
				LOGGER_DEBUG("Node Allocated: {}", i);
				return node;
			}
		}

		LOGGER_DEBUG("Failed to Allocate Node (No Space)");
		return nullptr;
	}

	void NodePool::DeallocateNode(NodeIndex index)
	{
		s_LastFreedNode = index;
		s_Blocks[index] = (uint8_t)BlockType::BlockFree;
		Node* node = GetNode(index);
		free(node->Data); // smartp?
		node->Index = -1;
		LOGGER_DEBUG("Node DeAllocated: {}", index);
	}

	Node* NodePool::GetNode(NodeIndex index)
	{
		if (!s_Pool) return nullptr;
		return &s_Pool[index];
	}

	Node* NodePool::GetNodeFromParent(NodeIndex parent, const std::string& name)
	{
		if (!s_Pool) return nullptr;
		for (NodeIndex i = 0; i < NODEPOOL_MAX_SIZE; i++)
		{
			Node* node = GetNode(i);
			if (node && node->IsValid() && node->Parent == parent && node->Data->Name == name) return node;
		}
		return nullptr;
	}
}
