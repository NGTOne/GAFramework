#include <sstream>
#include <string>
#include "1maxFitness.h"
#include "NonHierarchicalGenePool.h"

using namespace std;

OneMaxFitness::OneMaxFitness() : FitnessFunction() {}

int OneMaxFitness::checkFitness(GenePool ** pools, int * indexes, int genomeLength) {
	int total = 0;

	for (int i = 0; i < genomeLength; i++) {
		total += *(int*)pools[i]->getIndex(indexes[i]);
	}

	return total;
}

string OneMaxFitness::toString(GenePool ** pools, int * indexes, int genomeLength) {
	string returnString = "";
	stringstream ss;
	int * tempIntPtr;

	
	for (int i = 0; i < genomeLength; i++) {
		tempIntPtr = (int*)pools[i]->getIndex(indexes[i]);

		ss << *tempIntPtr;
	}

	returnString = ss.str();

	return returnString;
}
