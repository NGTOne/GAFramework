#include "../core/CrossoverOperation.hpp"
#pragma once

//N-point crossover is a generalization of the 1-point, 2-point, etc. crossover
//operations, allowing an arbitrary number n of points to be specified. If
//the genome is shorter than n, it tends to behave similarly to uniform
//crossover.
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
