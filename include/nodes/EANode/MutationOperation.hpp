#pragma once
#include "../../core/Genome.hpp"
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

	virtual int getNewLocusValue(
		int currentValue,
		int largestPossibleValue
	)=0;

	public:

	MutationOperation();
	MutationOperation(double newMutationRate);
	MutationOperation(double newMutationRate, unsigned newSeed);

	virtual Genome * mutate(
		Genome * initialGenome,
		int * largestPossibleValues
	);

	void init(double newMutationRate, unsigned newSeed);

	std::string toString();
};
