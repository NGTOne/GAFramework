#include "core/builders/StructureBuilder.hpp"
#include "exception/ValueOutOfRangeException.hpp"
#include "exception/InvalidNodeException.hpp"

std::tuple<unsigned int, unsigned int> StructureBuilder::findNode(
	std::string node
) {
	for (unsigned int i = 0; i < this->names.size(); i++)
		for (unsigned int k = 0; k < this->names[i].size(); k++)
			if (names[i][k] == node) return std::make_tuple(i, k);

	throw InvalidNodeException();
}

bool StructureBuilder::nodeExists(std::string node) {
	std::vector<std::string> allNodes;
	for (unsigned int i = 0; i < this->names.size(); i++)
		allNodes.insert(
			allNodes.end(),
			this->names[i].begin(),
			this->names[i].end()
		);

	for (unsigned int i = 0; i < allNodes.size(); i++)
		if (node == allNodes[i]) return true;
	return false;
}

bool StructureBuilder::nodesExist(std::vector<std::string> nodes) {
	for (unsigned int i = 0; i < nodes.size(); i++)
		if (this->nodeExists(nodes[i])) return true;
	return false;
}

unsigned int StructureBuilder::numLevels() {
	return this->names.size();
}

std::vector<unsigned int> StructureBuilder::getLevelSizes() {
	std::vector<unsigned int> sizes;
	for (unsigned int i = 0; i < this->names.size(); i++)
		sizes.push_back(this->names[i].size());

	return sizes;
}

std::vector<std::string> StructureBuilder::getLevel(unsigned int level) {
	if (level >= this->numLevels()) throw ValueOutOfRangeException();
	return this->names[level];
}
