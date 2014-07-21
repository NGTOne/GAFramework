#include <sstream>
#include <string>
#include <libGAFramework/GAFramework.hpp>
#include "Hier1maxFitness.hpp"

using namespace std;

HierOneMaxFitness::HierOneMaxFitness() : FitnessFunction() {}

PropertiesList * HierOneMaxFitness::checkFitness(GenePool ** pools, int * indexes, int genomeLength) {
	int total = 0;
	Individual * tempIndividual;
	PropertiesList * returnProperties = new PropertiesList();
	PropertiesList * tempProperties;

	for (int i = 0; i < genomeLength; i++) {
		tempIndividual = (Individual*)pools[i]->getIndex(indexes[i]);
		
		tempProperties = tempIndividual->getProperties();

		total += tempProperties->getFitness();
	}

	returnProperties->setFitness(total);

	return returnProperties;
}

string HierOneMaxToString::toString(GenePool ** pools, int * indexes, int genomeLength) {
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
