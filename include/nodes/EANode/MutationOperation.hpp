#pragma once
#include "../../core/Genome.hpp"
#include "../../core/GenomeTemplate.hpp"
#include <random>
#include <string>

/*
* This abstract class allows the creation of any mutation operator that is
* desired.
*/

class MutationOperation {
	private:

	protected:
	unsigned int seed;
        double mutationRate;
	std::mt19937 generator;

	virtual unsigned int getNewLocusValue(
		unsigned int currentValue,
		unsigned int largestPossibleValue
	)=0;
	unsigned int getNewLocusValue(
		std::tuple<unsigned int, Locus*> existing
	);

	void init(double mutationRate, unsigned int seed);

	public:
	MutationOperation();
	MutationOperation(double mutationRate);
	MutationOperation(double mutationRate, unsigned int seed);
	virtual ~MutationOperation();

	virtual Genome * mutate(Genome * initialGenome);
	GenomeTemplate mutate(GenomeTemplate initial);

	std::string toString();
};
