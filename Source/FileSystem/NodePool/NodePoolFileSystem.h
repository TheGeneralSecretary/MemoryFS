#pragma once

#include "FileSystem/FileSystem.h"
#include "FileSystem/NodePool/NodePool.h"

namespace MemoryFS
{
	class NodePoolFileSystem : public FileSystem
	{
	public:
		virtual bool Init() override;
		virtual void Destroy() override;
		virtual bool MkFile(const std::string& path) override;
		virtual const struct stat& GetAttr(const std::string& path) override;
		virtual Node* GetNode(NodeIndex index) override;
		virtual Node* GetNode(const std::string& path) override;
		virtual DNode ReadDir(const std::string& path) override;

		// TESTER
		void PrintTest()
		{
			for (int i = 0; i < NODEPOOL_MAX_SIZE; i++)
			{
				Node* node = NodePool::GetNode(i);
				if (node->IsValid())
				{
					std::string children;
					std::cout << "Name: " << node->Data->Name << std::endl;
					std::cout << "Index: " << node->Index << std::endl;
					std::cout << "Parent: " << node->Parent << std::endl;
					std::cout << "Type: " << NodeTypeStr[(int)node->Type] << std::endl;
					if (node->HasChildren())
					{
						std::cout << "Children: \n";
						for (NodeIndex i = 0; i < NODE_MAX_CHILD; i++)
							if(node->Children->Children[i] != NODE_INVALID_NODE)
								children += std::to_string(node->Children->Children[i]) + " ";
						std::cout << "\t" << children << std::endl;
					}
					std::cout << "\n";
				}
			}
		}

	private:
		bool MkNode(const std::string& path, NodeType type);
		bool AddChild(Node* parent, const std::string& name, NodeType type);
		Node* GetParentNode(const std::string& path);

	private:
		Node* m_Root;
	};
}
