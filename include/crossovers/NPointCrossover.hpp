#include "../core/CrossoverOperation.hpp"
#pragma once

/*
* The n-point crossover operator selects up to n different points along the
* parents' genome. It then generates a mask using these points as swap
* locations - places where the parent that is providing the genetic
* information switches until the next point.
*
* EXAMPLE:
* N=4
* Points:        |   | ||
* Mask:        0011110010
* Parent 1:    ABBBDCCBDA
* Parent 2:    BBCDABDACC
* Offspring 1: ABCDABCBCA
* Offspring 2: BBBBDCDADC
*/

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
