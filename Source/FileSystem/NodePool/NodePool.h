#pragma once

#include <string>
#include <sys/stat.h>

#define NODEPOOL_INVALID_NODE -1
#define NODEPOOL_MAX_SIZE 128

namespace MemoryFS
{
	using NodeIndex = int32_t;

	enum class NodeType
	{
		DIRECTORY,
		FILE
	};
	static const char* NodeTypeStr[] = { "DIRECTORY", "FILE" };

	struct NodeData
	{
		std::string Name;
		std::string Content;
		struct stat st;
	};

	struct NodeChildren
	{
		int Count;
		NodeIndex Children[NODEPOOL_MAX_SIZE];

		NodeChildren()
		{
			Count = 0;
			memset(Children, NODEPOOL_INVALID_NODE, NODEPOOL_MAX_SIZE * sizeof(NodeIndex));
		}
	};

	struct Node
	{
		NodeIndex Index;
		NodeIndex Parent;
		NodeType Type;
		NodeData* Data; // smart pointer?
		NodeChildren* Children;

		Node()
		{
			Index = -1;
			Parent = -1;
			Type = NodeType::DIRECTORY;
			Data = nullptr;
			Children = nullptr;
		}

		bool IsValid() const { return Index != NODEPOOL_INVALID_NODE; }
		bool IsDir() const { return Type == NodeType::DIRECTORY; }
		bool IsFile() const { return Type == NodeType::FILE; }
		bool HasChildren() const { return Children && Children->Count > 0; }
	};

	static NodeData* CreateNodeData(const std::string& name)
	{
		NodeData* data = new NodeData;
		if (!data) return nullptr;
		memset(&data->st, 0, sizeof(struct stat));
		data->Name = name;
		return data;
	}

	static void InitializeNodeStat(Node* node)
	{
		if (node->IsDir())
		{
			node->Data->st.st_uid = 0;
			node->Data->st.st_gid = 0;
			node->Data->st.st_mode = S_IFDIR | 0755;
			node->Data->st.st_nlink = 2;
			node->Data->st.st_size = 1024;
		}
		else if (node->IsFile())
		{
			node->Data->st.st_uid = 0;
			node->Data->st.st_gid = 0;
			node->Data->st.st_mode = S_IFREG | 0644;
			node->Data->st.st_nlink = 1;
			node->Data->st.st_size = 1024;
		}
	}

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
