#include "../core/CrossoverOperation.hpp"
#pragma once

/*
* Cut-and-splice crossover takes the two parents, selects different,
* arbitrary points along each of their genomes, and then copies everything
* replaces everything after the first parent's point with everything after
* the second parent's (and vice versa). The offspring are the result of this,
* and may have genomes of different lengths than those of their parents.
*
* EXAMPLE:
* Parent 1:    ABBBDB|CD
* Parent 2:    BBCD|AABD
* Offspring 1: ABBBDBAABD
* Offspring 2: BBCDCD
*
* WARNING: Selection pressures may result in VERY LONG offspring genomes
* within a few generations. Use this operator with great care.
*/

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
