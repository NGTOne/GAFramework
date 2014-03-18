#include <sstream>
#include <string>
#include "1maxFitness.h"

using namespace std;

int OneMaxFitness::checkFitness(GenePool ** pools, int indexes[], int genomeLength) {
	int total = 0;

	for (int i = 0; i < genomeLength; i++) {
		total += (int)pools[i]->getIndex(indexes[i]);
	}

	return total;
}

string OneMaxFitness::toString(GenePool ** pools, int indexes[], int genomeLength) {
	string returnString = "";
	stringstream ss;

	for (int i = 0; i < genomeLength; i++) {
		ss << (int)pools[i]->getIndex(indexes[i]);
	}

	returnString = ss.str();

	return returnString;
}
