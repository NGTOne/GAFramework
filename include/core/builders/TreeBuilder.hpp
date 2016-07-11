#include <vector>
#include <tuple>
#pragma once

class TreeBuilder {
	private:

	protected:
	std::vector<std::vector<unsigned int>> counts;
	std::vector<std::vector<std::string>> names;

	std::tuple<unsigned int, unsigned int> findNode(std::string node);
	bool nodeExists(std::string node);

	public:
	TreeBuilder(std::string root);
	TreeBuilder addSubNode(std::string node, std::string subNode);
	TreeBuilder addSubNodes(
		std::string node,
		std::vector<std::string> subNodes
	);

	unsigned int numLevels();
	std::vector<unsigned int> getLevelSizes();
	std::vector<unsigned int> getLevelCounts(unsigned int level);
	std::vector<std::string> getLevel(unsigned int level);
};
