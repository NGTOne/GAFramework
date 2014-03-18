//Abstract class for mutation operators. Lets us define any mutation operation we like.
#pragma once
#include <random>

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

	virtual int * mutate(int * initialGenome, int * largestPossibleValues, int genomeLength)=0;

	void init(double newMutationRate, unsigned newSeed);
};
