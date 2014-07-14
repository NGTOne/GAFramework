#include "../core/CrossoverOperation.hpp"
#pragma once

//"Cut and splice" crossover takes the two parent genomes, picks a different
//point on each, and transplants everything after that point to the
//corresponding point on the other. It is distinct from one-point crossover
//by the fact that the offspring may be of different lengths than the
//parents.
class CutAndSpliceCrossover : public CrossoverOperation {
	private:

	protected:
	
	int numPoints;

	public:

	CutAndSpliceCrossover();
	CutAndSpliceCrossover(unsigned newSeed);
	
	Genome ** crossOver(Genome * firstGenome, Genome * secondGenome);

	std::string toString();

};
