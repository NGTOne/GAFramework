#include <sstream>
#include <string>
#include <libGAFramework/GAFramework.hpp>
#include "1maxFitness.hpp"

using namespace std;

OneMaxFitness::OneMaxFitness() : FitnessFunction() {}

PropertiesList * OneMaxFitness::checkFitness(GenePool ** pools, int * indexes, int genomeLength) {
	int total = 0;

	for (int i = 0; i < genomeLength; i++) {
		total += *(int*)pools[i]->getIndex(indexes[i]);
	}
	
	PropertiesList * returnProperties = new PropertiesList();

	returnProperties->setFitness(total);

	return returnProperties;
}

string OneMaxToString::toString(GenePool ** pools, int * indexes, int genomeLength) {
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
