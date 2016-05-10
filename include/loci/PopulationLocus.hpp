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
	bool outOfRange(int i);

	std::string toString();
	std::string flatten(int index);
};
