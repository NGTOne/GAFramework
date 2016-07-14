#include <vector>
#include <tuple>
#include <string>
#pragma once

class StructureBuilder {
	private:

	protected:
	std::vector<std::vector<std::string>> names;

	std::tuple<unsigned int, unsigned int> findNode(std::string node);
	bool nodeExists(std::string node);
	bool nodesExist(std::vector<std::string> nodes);

	public:
	unsigned int numLevels();
	std::vector<unsigned int> getLevelSizes();
	std::vector<std::string> getLevel(unsigned int level);
};
