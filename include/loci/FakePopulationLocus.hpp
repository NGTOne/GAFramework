#include "PopulationLocus.hpp"
#include "../core/Genome.hpp"
#include <vector>
#include <string>
#pragma once

// This "locus" type is useful for apportionment, because it allows us
// to selectively and transparently replace a genome with one of our choosing

class FakePopulationLocus: public PopulationLocus {
	private:

	protected:
	Genome * target;

	public:
	FakePopulationLocus(Genome * target, PopulationNode * targetBase);
	~FakePopulationLocus();

	Genome * getIndex(unsigned int index);
	unsigned int randomIndex();
	unsigned int topIndex();
	bool outOfRange(unsigned int i);

	std::string toString();
	std::string flatten(unsigned int index);
	Genome flattenToGenome(unsigned int index);
};