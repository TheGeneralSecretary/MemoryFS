#include "buildpch.h"
#include "FileSystem/NodePool/PathParser.h"

#include <regex>

namespace MemoryFS
{
	NodePath NodePathParse(const std::string& path)
	{
		std::string tmp = path;
		std::regex pattern("(?:[^/]|//)+");
		std::regex_token_iterator<std::string::iterator> reg(tmp.begin(), tmp.end(), pattern);
		std::regex_token_iterator<std::string::iterator> rend;
		std::vector<std::string> parts = { reg, rend };
		std::string target = parts.size() ? parts[parts.size() - 1] : "";
		return { path, parts, std::string(1, path[0]), target };
	}
}
