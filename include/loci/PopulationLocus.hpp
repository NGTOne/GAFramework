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

	Genome * getIndex(int index);
	int randomIndex();
	int topIndex();
	bool isConstructive();
	bool outOfRange(int i);

	std::string toString();
	std::string nodeName();
	std::string flatten(int index);
};
