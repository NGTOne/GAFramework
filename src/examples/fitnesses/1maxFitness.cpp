#include <sstream>
#include <string>
#include <libHierGA/HierGA.hpp>
#include "1maxFitness.hpp"

using namespace std;

OneMaxFitness::OneMaxFitness() : ObjectiveFunction() {}

Fitness OneMaxFitness::checkFitness(Genome* genome) {
	unsigned total = 0;
	Genome flattened = genome->flattenGenome();

	for (unsigned int i = 0; i < flattened.genomeLength(); i++)
		total += flattened.getIndex<int>(i);

	return Fitness(total, FitnessSource(this));
}

OneMaxToString::OneMaxToString(
	HierarchicalToString::mode printMode
) : HierarchicalToString(printMode) {}

std::string OneMaxToString::stringifySegment(std::vector<Gene*> genes) {
	stringstream ss;
	
	for (unsigned int i = 0; i < genes.size(); i++)
		ss << genes[i]->getValue<int>();
		
	return ss.str();
}
