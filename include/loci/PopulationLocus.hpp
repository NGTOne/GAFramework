#include "../core/Locus.hpp"
#include "../core/Genome.hpp"
#include "../core/PopulationNode.hpp"
#include <vector>
#include <string>
#pragma once

class PopulationLocus: public Locus {
	private:

	protected:
	PopulationNode * node;

	public:
	PopulationLocus(PopulationNode * node);
	~PopulationLocus();

	Genome * getIndex(unsigned int index);
	unsigned int randomIndex();
	unsigned int topIndex();
	bool isConstructive();
	bool outOfRange(unsigned int i);

	std::string toString();
	std::string nodeName();
	std::string flatten(unsigned int index);
};
