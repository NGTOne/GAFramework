#include "../nodes/EANode/CrossoverOperation.hpp"
#include <vector>
#pragma once

/*
* Cut-and-splice crossover takes the two parents, selects different,
* arbitrary points along each of their genomes, and then
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
	Genome * createOffspring(
		vector<Genome*> parents,
		vector<unsigned int> points
	);

	public:
	CutAndSpliceCrossover();
	CutAndSpliceCrossover(unsigned int numOffspring);
	CutAndSpliceCrossover(unsigned int numOffspring, unsigned seed);
	
	std::vector<Genome*> crossOver(std::vector<Genome*> genomes);
	std::string toString();
};
