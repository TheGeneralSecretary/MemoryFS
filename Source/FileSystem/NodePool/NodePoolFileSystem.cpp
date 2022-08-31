#include "buildpch.h"
#include "FileSystem/NodePool/NodePoolFileSystem.h"
#include "FileSystem/NodePool/PathParser.h"
#include "Util/Logger.h"

namespace MemoryFS
{
	bool NodePoolFileSystem::Init()
	{
		if (!NodePool::Init()) return false;
		m_Root = NodePool::GetPool();
		LOGGER_DEBUG("Initialized NodePoolFileSystem");
		return true;
	}

	void NodePoolFileSystem::Destroy()
	{
		NodePool::Destroy();
		LOGGER_DEBUG("Destroyed NodePoolFileSystem");
	}

	bool NodePoolFileSystem::MkFile(const std::string& path)
	{
		return MkNode(path, NodeType::FILE);
	}

	const struct stat& NodePoolFileSystem::GetAttr(const std::string& path)
	{
		Node* node = GetNode(path);
		if (node)
		{
			//LOGGER_DEBUG("RETURNED ATTR FOR: {}", path);
			return node->Data->st;
		}

		// UNKNOWN FILES
		static struct stat stdef
		{
			.st_mode = S_IFREG | 0644,
			.st_nlink = 1,
			.st_uid = 0,
			.st_gid = 0,
			.st_size = 1024,
		};

		LOGGER_DEBUG("RETURNED DEFAULT FOR: {}", path);
		return stdef;
	}

	Node* NodePoolFileSystem::GetNode(NodeIndex index)
	{
		Node* node = NodePool::GetNode(index);
		if (node && node->IsValid()) return node;
		return nullptr;
	}

	Node* NodePoolFileSystem::GetNode(const std::string& path)
	{
		NodePath nodepath = NodePathParse(path);
		if (nodepath.root != "/") return nullptr;
		if (nodepath.parts.size() == 0) return m_Root; // optimize

		Node* node = m_Root;
		for (int i = 0; i < nodepath.parts.size(); i++)
		{
			node = NodePool::GetNodeFromParent(node->Index, nodepath.parts[i]);
			if (!node)
			{
				LOGGER_DEBUG("No Node: {}", path);
				return nullptr;
			}
		}

		return node;
	}

	DNode NodePoolFileSystem::ReadDir(const std::string& path)
	{
		Node* dir = GetNode(path);
		if (!dir) return {};

		if (dir->IsFile())
		{
			LOGGER_DEBUG("{} is not a directory", path);
			return {};
		}

		if (!dir->HasChildren()) return {};

		DNode dnode;
		dnode.NodeCount = dir->Children->Count;
		
		for (NodeIndex i = 0, j = 0; i < NODE_MAX_CHILD; i++)
			if (dir->Children->Children[i] != NODE_INVALID_NODE)
				dnode.Nodes[j++] = dir->Children->Children[i];

		return dnode;
	}

	bool NodePoolFileSystem::MkNode(const std::string& path, NodeType type)
	{
		if (path == "/")
		{
			LOGGER_DEBUG("Cannot Create Node: '/'");
			return false;
		}

		Node* parent = GetParentNode(path);
		if (!parent) return false;

		if (parent->IsFile())
		{
			LOGGER_DEBUG("Cannot Create {} within FILE", NodeTypeStr[(int)type]);
			return false;
		}

		std::string target = path.substr(1, path.find_last_of("/") - 1);
		if (NodePool::GetNodeFromParent(parent->Index, target))
		{
			LOGGER_DEBUG("{} already exists", NodeTypeStr[(int)type]);
			return false;
		}

		return AddChild(parent, target, type);
	}

	bool NodePoolFileSystem::AddChild(Node* parent, const std::string& name, NodeType type)
	{
		NodeIndex free = NODE_INVALID_NODE;
		for (free = 0; free < NODE_MAX_CHILD; free++)
			if (parent->Children->Children[free] == NODE_INVALID_NODE)
				break;

		if (free == NODE_INVALID_NODE)
		{
			LOGGER_DEBUG("Failed To Create Child (No Space)");
			return false;
		}

		Node* node = NodePool::AllocateNode();
		node->Parent = parent->Index;
		node->Type = type;
		node->Children = new NodeChildren;
		node->Data = CreateNodeData(name);
		InitializeNodeStat(node);

		parent->Children->Children[free] = node->Index;
		parent->Children->Count++;
		return true;
	}

	Node* NodePoolFileSystem::GetParentNode(const std::string& path)
	{
		NodePath nodepath = NodePathParse(path);
		if (nodepath.root != "/") return nullptr;
		if (nodepath.parts.size() == 0) return nullptr; // ROOT OR NULL?

		Node* parent = m_Root;
		for (NodeIndex i = 0; i < nodepath.parts.size() - 1; i++)
		{
			parent = NodePool::GetNodeFromParent(parent->Index, nodepath.parts[i]);
			if (!parent)
			{
				LOGGER_DEBUG("No Parent Directory: {}", path);
				return nullptr;
			}
		}

		return parent;
	}
}
