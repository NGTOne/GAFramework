#ifndef NODES_EANODE_CROSSOVERS_CutAndSpliceCrossover
#define NODES_EANODE_CROSSOVERS_CutAndSpliceCrossover

#include "../CrossoverOperation.hpp"
#include <vector>

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

// TODO: Figure out whether I should keep this operator at all

class CutAndSpliceCrossover : public CrossoverOperation {
	private:

	protected:
	GenomeTemplate createOffspring(
		std::vector<GenomeTemplate> parents,
		std::vector<unsigned int> points
	);
	std::vector<GenomeTemplate> crossOver(
		std::vector<GenomeTemplate> parents
	);

	public:
	CutAndSpliceCrossover();
	CutAndSpliceCrossover(unsigned int numOffspring);
	
	std::string toString();
};

#endif
