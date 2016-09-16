#include <sstream>
#include <string>
#include <libHierGA/HierGA.hpp>
#include "1maxFitness.hpp"

using namespace std;

OneMaxFitness::OneMaxFitness() : ObjectiveFunction() {}

float OneMaxFitness::checkFitness(Genome * genome) {
	unsigned total = 0;
	Genome flattened = genome->flattenGenome();

	for (unsigned int i = 0; i < 32 && i < genome->genomeLength(); i++)
		total += flattened.getIndex<int>(i);

	return total;
}

string OneMaxToString::toString(Genome * genome) {
	stringstream ss;
	Genome flattened = genome->flattenGenome();
	
	for (unsigned int i = 0; i < 32 && i < genome->genomeLength(); i++)
		ss << flattened.getIndex<int>(i);
		
	return ss.str();
}
