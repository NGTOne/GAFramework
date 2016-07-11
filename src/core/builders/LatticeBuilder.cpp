#include "core/builders/LatticeBuilder.hpp"
#include "exception/ValueOutOfRangeException.hpp"
#include "exception/NodeAlreadyExistsException.hpp"

LatticeBuilder::LatticeBuilder() {}

LatticeBuilder::LatticeBuilder(std::string topNode) {
	this->names.push_back({topNode});
}

LatticeBuilder::LatticeBuilder(std::vector<std::string> topNodes) {
	this->names.push_back(topNodes);
}

LatticeBuilder::LatticeBuilder(std::vector<std::vector<std::string>> nodes) {
	this->names = nodes;
}

LatticeBuilder LatticeBuilder::addNode(std::string node, unsigned int row) {
	this->checkValid(node, row, 0);
	this->names[row].push_back(node);
	return *this;
}

LatticeBuilder LatticeBuilder::addNodes(
	std::vector<std::string> nodes,
	unsigned int row
) {
	this->checkValid(nodes, row, 0);
	this->names[row].insert(
		this->names[row].end(),
		nodes.begin(),
		nodes.end()
	);
	return *this;
}

LatticeBuilder LatticeBuilder::addNode(
	std::string node,
	unsigned int row,
	unsigned int index
) {
	this->checkValid(node, row, index);
	this->names[row].insert(this->names[row].begin() + index, node);
	return *this;
}

LatticeBuilder LatticeBuilder::addNodes(
	std::vector<std::string> nodes,
	unsigned int row,
	unsigned int index
) {
	this->checkValid(nodes, row, index);
	this->names[row].insert(
		this->names[row].begin() + index,
		nodes.begin(),
		nodes.end()
	);
	return *this;
}

LatticeBuilder LatticeBuilder::addRow(std::string node) {
	if (this->nodeExists(node)) throw NodeAlreadyExistsException();
	this->names.push_back({node});
	return *this;
}

LatticeBuilder LatticeBuilder::addRow(std::vector<std::string> nodes) {
	if (this->nodesExist(nodes)) throw NodeAlreadyExistsException();
	this->names.push_back(nodes);
	return *this;
}

LatticeBuilder LatticeBuilder::addRow(std::string node, unsigned int row) {
	this->checkValid(node, row, 0);
	this->names.insert(this->names.begin() + row, {node});
	return *this;
}

LatticeBuilder LatticeBuilder::addRow(
	std::vector<std::string> nodes,
	unsigned int row
) {
	this->checkValid(nodes, row, 0);
	this->names.insert(this->names.begin() + row, nodes);
	return *this;
}

void LatticeBuilder::checkValid(
	std::string node,
	unsigned int row,
	unsigned int index
) {
	if (this->nodeExists(node)) throw NodeAlreadyExistsException();
	if (row >= this->names.size()) throw ValueOutOfRangeException();
	if (index >= this->names[row].size()) throw ValueOutOfRangeException();
}

void LatticeBuilder::checkValid(
	std::vector<std::string> nodes,
	unsigned int row,
	unsigned int index
) {
	if (this->nodesExist(nodes)) throw NodeAlreadyExistsException();
	this->checkValid(nodes[0], row, index);
}
