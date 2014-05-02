#include "CrossoverOperation.h"
#pragma once

class NPointCrossover : public CrossoverOperation {
	private:

	protected:
	
	int numPoints;

	public:

	NPointCrossover(int newNumPoints);
	NPointCrossover(int newNumPoints, unsigned newSeed);
	
	Genome ** crossOver(int firstGenome[], int secondGenome[], int firstGenomeLength, int secondGenomeLength);

	std::string toString();

};
