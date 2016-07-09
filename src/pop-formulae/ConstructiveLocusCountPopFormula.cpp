#include "pop-formulae/ConstructiveLocusCountPopFormula.hpp"
#include "exception/ValueOutOfRangeException.hpp"

unsigned int ConstructiveLocusCountPopFormula::getPopulationSize(
	std::vector<Locus*> loci
) {
	unsigned int numConstructives = 0;
	for (unsigned int i = 0; i < loci.size(); i++)
		if (loci[i]->isConstructive()) numConstructives++;

	return (numConstructives > 0 ? numConstructives : loci.size());
}
