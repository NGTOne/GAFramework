#include <sstream>
#include <string>
#include <libHierGA/HierGA.hpp>
#include "1maxFitness.hpp"

using namespace std;

OneMaxFitness::OneMaxFitness() : ObjectiveFunction() {}

float OneMaxFitness::checkFitness(Genome * genome) {
	unsigned total = 0;
	Genome flattened = genome->flattenGenome();

	for (unsigned int i = 0; i < 32; i++)
		total += flattened.getIndex<int>(i);

	return total;
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
