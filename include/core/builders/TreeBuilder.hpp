#include <vector>
#include "StructureBuilder.hpp"
#pragma once

class TreeBuilder: public StructureBuilder {
	private:

	protected:
	std::vector<std::vector<unsigned int>> counts;

	public:
	TreeBuilder(std::string root);
	TreeBuilder addSubNode(std::string node, std::string subNode);
	TreeBuilder addSubNodes(
		std::string node,
		std::vector<std::string> subNodes
	);

	std::vector<unsigned int> getLevelCounts(unsigned int level);
};
