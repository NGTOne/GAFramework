#include "CrossoverOperation.hpp"
#pragma once

class NPointCrossover : public CrossoverOperation {
	private:

	protected:
	
	int numPoints;

	public:

	NPointCrossover(int newNumPoints);
	NPointCrossover(int newNumPoints, unsigned newSeed);
	
	Genome ** crossOver(Genome * firstGenome, Genome * secondGenome);

	std::string toString();

};
