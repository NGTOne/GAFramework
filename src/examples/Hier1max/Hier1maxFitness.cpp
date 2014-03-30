#include <sstream>
#include <string>
#include "Hier1maxFitness.h"
#include "NonHierarchicalGenePool.h"
#include "Individual.h"

using namespace std;

HierOneMaxFitness::HierOneMaxFitness() : FitnessFunction() {}

int HierOneMaxFitness::checkFitness(GenePool ** pools, int * indexes, int genomeLength) {
	int total = 0;
	Individual * tempIndividual;

	for (int i = 0; i < genomeLength; i++) {
		tempIndividual = (Individual*)pools[i]->getIndex(indexes[i]);

		total += tempIndividual->checkFitness();
	}

	return total;
}

string HierOneMaxFitness::toString(GenePool ** pools, int * indexes, int genomeLength) {
	string returnString = "";
	stringstream ss;
	int * tempIntPtr;
	Individual * tempIndividual;	

	for (int i = 0; i < genomeLength; i++) {
		tempIndividual = (Individual*)pools[i]->getIndex(indexes[i]);

		ss << tempIndividual->toGenomeString();
	}

	returnString = ss.str();

	return returnString;
}
