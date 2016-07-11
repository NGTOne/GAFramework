#include "core/builders/TreeBuilder.hpp"
#include "exception/InvalidNodeException.hpp"
#include "exception/NodeAlreadyExistsException.hpp"
#include "exception/ValueOutOfRangeException.hpp"

TreeBuilder::TreeBuilder(std::string root) {
	this->counts.push_back(std::vector<unsigned int>(1, 0));
	this->names.push_back(std::vector<std::string>({root}));
}

TreeBuilder TreeBuilder::addSubNode(std::string node, std::string subNode) {
	return this->addSubNodes(node, std::vector<std::string>({subNode}));
}

TreeBuilder TreeBuilder::addSubNodes(
	std::string node,
	std::vector<std::string> subNodes
) {
	for (unsigned int i = 0; i < subNodes.size(); i++)
		if (this->nodeExists(subNodes[i]))
			throw NodeAlreadyExistsException();

	unsigned int nodeRow, nodeCol, nodeOffset;
	std::tie(nodeRow, nodeCol) = this->findNode(node);
	nodeOffset = 0;
	for (unsigned int i = 0; i <= nodeCol; i++)
		nodeOffset += this->counts[nodeRow][i];

	if (nodeRow == this->numLevels() - 1) {
		this->counts.push_back(std::vector<unsigned int>());
		this->names.push_back(std::vector<std::string>());
	}

	for (unsigned int i = 0; i < subNodes.size(); i++) {
		this->names[nodeRow+1].insert(
			this->names[nodeRow+1].begin() + nodeOffset + i,
			subNodes[i]
		);
		this->counts[nodeRow+1].insert(
			this->counts[nodeRow+1].begin() + nodeOffset + i,
			0
		);
	}

	this->counts[nodeRow][nodeCol] += subNodes.size();

	return *this;
}

std::tuple<unsigned int, unsigned int> TreeBuilder::findNode(
	std::string node
) {
	for (unsigned int i = 0; i < this->names.size(); i++)
		for (unsigned int k = 0; k < this->names[i].size(); k++)
			if (names[i][k] == node) return std::make_tuple(i, k);

	throw InvalidNodeException();
}

bool TreeBuilder::nodeExists(std::string node) {
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

unsigned int TreeBuilder::numLevels() {
	return this->names.size();
}

std::vector<unsigned int> TreeBuilder::getLevelSizes() {
	std::vector<unsigned int> sizes;
	for (unsigned int i = 0; i < this->names.size(); i++)
		sizes.push_back(this->names[i].size());

	return sizes;
}

std::vector<unsigned int> TreeBuilder::getLevelCounts(unsigned int level) {
	if (level >= this->numLevels()) throw ValueOutOfRangeException();
	return this->counts[level];
}

std::vector<std::string> TreeBuilder::getLevel(unsigned int level) {
	if (level >= this->numLevels()) throw ValueOutOfRangeException();
	return this->names[level];
}
