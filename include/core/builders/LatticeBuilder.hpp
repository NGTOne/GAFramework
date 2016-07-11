#include "StructureBuilder.hpp"
#include <vector>
#pragma once

class LatticeBuilder: public StructureBuilder {
	private:

	protected:
	void checkValid(
		std::string node,
		unsigned int row,
		unsigned int index
	);
	void checkValid(
		std::vector<std::string> node,
		unsigned int row,
		unsigned int index
	);

	public:
	LatticeBuilder();
	LatticeBuilder(std::string topNode);
	LatticeBuilder(std::vector<std::string> topNodes);
	LatticeBuilder(std::vector<std::vector<std::string>> nodes);

	LatticeBuilder addNode(std::string node, unsigned int row);
	LatticeBuilder addNodes(
		std::vector<std::string> nodes,
		unsigned int row
	);
	LatticeBuilder addNode(
		std::string node,
		unsigned int row,
		unsigned int index
	);
	LatticeBuilder addNodes(
		std::vector<std::string> nodes,
		unsigned int row,
		unsigned int index
	);

	LatticeBuilder addRow(std::string node);
	LatticeBuilder addRow(std::vector<std::string> nodes);
	LatticeBuilder addRow(std::string node, unsigned int row);
	LatticeBuilder addRow(
		std::vector<std::string> nodes,
		unsigned int row
	);
};
