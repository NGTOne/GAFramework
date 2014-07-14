#pragma once
#include "Genome.hpp"
#include <random>
#include <string>

//The MutationOperation abstract class allows us to define any GA mutation
//operators that we please.
class MutationOperation {
	private:

	protected:
	unsigned seed;
        double mutationRate;
	std::mt19937 generator;

	public:

	MutationOperation();
	MutationOperation(double newMutationRate);
	MutationOperation(double newMutationRate, unsigned newSeed);

	virtual Genome * mutate(Genome * initialGenome, int * largestPossibleValues)=0;

	void init(double newMutationRate, unsigned newSeed);

	std::string toString();
};
