#pragma once

#include <string>
#include <sys/stat.h>
#include <FileSystem/Node.h>

namespace MemoryFS
{
	struct DNode
	{
		int NodeCount;
		NodeIndex Nodes[NODE_MAX_CHILD];

		DNode()
		{
			NodeCount = 0;
			memset(Nodes, NODE_INVALID_NODE, sizeof(NodeIndex) * NODE_MAX_CHILD);
		}
	};

	class FileSystem
	{
	public:
		virtual bool Init() = 0;
		virtual void Destroy() = 0;
		virtual bool MkFile(const std::string& path) = 0;
		virtual bool MkDir(const std::string& path) = 0;
		virtual const struct stat& GetAttr(const std::string& path) = 0;
		virtual Node* GetNode(NodeIndex index) = 0;
		virtual Node* GetNode(const std::string& path) = 0;
		virtual DNode ReadDir(const std::string& path) = 0;
	};
}
