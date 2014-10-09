#pragma once
#include "Genome.hpp"
#include <random>
#include <string>

/*
* This abstract class allows the creation of any mutation operator that is
* desired.
*/

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
