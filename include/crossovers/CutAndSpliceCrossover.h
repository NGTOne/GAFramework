#include "CrossoverOperation.h"
#pragma once

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
