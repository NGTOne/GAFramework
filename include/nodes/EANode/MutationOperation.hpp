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

	virtual unsigned int getNewLocusValue(
		unsigned int currentValue,
		unsigned int largestPossibleValue
	)=0;

	void init(double mutationRate, unsigned seed);

	public:
	MutationOperation();
	MutationOperation(double mutationRate);
	MutationOperation(double mutationRate, unsigned seed);
	virtual ~MutationOperation();

	virtual Genome * mutate(Genome * initialGenome);

	std::string toString();
};
