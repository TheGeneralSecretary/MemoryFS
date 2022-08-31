#pragma once

#include <string>
#include <vector>

namespace MemoryFS
{
	struct NodePath
	{
		std::string path;
		std::vector<std::string> parts;
		std::string root;
		std::string target;
	};

	NodePath NodePathParse(const std::string& path);
}
