#include <sstream>
#include <string>
#include <libGAFramework/GAFramework.hpp>
#include "Hier1maxFitness.hpp"

using namespace std;

HierOneMaxFitness::HierOneMaxFitness() : FitnessFunction() {}

int * HierOneMaxFitness::checkFitness(GenePool ** pools, int * indexes, int genomeLength) {
	int total = 0;
	Individual * tempIndividual;
	int * returnProperties = (int*)malloc(sizeof(int)*2);
	int * tempProperties;

	for (int i = 0; i < genomeLength; i++) {
		tempIndividual = (Individual*)pools[i]->getIndex(indexes[i]);
		
		tempProperties = tempIndividual->getProperties();

		total += tempProperties[1];
	}

	returnProperties[0] = 2;
	returnProperties[1] = total;

	return returnProperties;
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
