#include <sstream>
#include <string>
#include <libHierGA/HierGA.hpp>
#include "HierLongestFragmentFitness.hpp"

using namespace std;

HierLongestFragmentFitness::HierLongestFragmentFitness() : FitnessFunction() {}

PropertiesList * HierLongestFragmentFitness::checkFitness(GeneNode ** pools, int * indexes, int genomeLength) {
	Individual * tempIndividual;
	Genome * tempGenome;
	PropertiesList * returnProperties = new PropertiesList(0);
	Genome ** tempGenomeList = NULL;
	int numGenomes = 0;
	int length = 0;
	int * fullIndexes = NULL;
	GeneNode ** fullPools = NULL;

	//Get the second (middle) level - we're evaluating at the top (first)
	//level, so we have to retrieve the second and third (middle and
	//bottom) to get the full genome
	//TODO: Write some methods to automatically flatten the tree and
	//return the result
	for (int i = 0; i < genomeLength; i++) {
		tempIndividual = (Individual*)pools[i]->getIndex(indexes[i]);
		tempGenome = tempIndividual->getGenome();

		int tempLength = tempGenome->getGenomeLength();
		GeneNode ** tempPools = tempGenome->getGeneNodes();
		int * tempIndexes = tempGenome->getGenome();

		//Get the genomes at the bottom level
		for (int k = 0; k < tempLength; k++) {
			tempGenomeList = (Genome**)realloc(tempGenomeList, (sizeof(Genome) * numGenomes) + sizeof(Genome));

			Individual * tempIndividual = (Individual*)tempPools[k]->getIndex(tempIndexes[k]);
			tempGenomeList[numGenomes++] = tempIndividual->getGenome();
		}
	}

	//Get the length of the fully assembled genome and flatten out the
	//tree
	for (int i = 0; i < numGenomes; i++) {
		length += tempGenomeList[i]->getGenomeLength();
		fullIndexes = (int*)realloc(fullIndexes, sizeof(int)*length);
		fullPools = (GeneNode**)realloc(fullPools, sizeof(GeneNode*)*length);

		int currentInternalIndex = 0;
		int * tempIndexes = tempGenomeList[i]->getGenome();
		GeneNode ** tempPools = tempGenomeList[i]->getGeneNodes();

		for (int k = length - tempGenomeList[i]->getGenomeLength(); k < length; k++) {
			fullIndexes[k] = tempIndexes[currentInternalIndex];
			fullPools[k] = tempPools[currentInternalIndex++];
		}
	}

	free(tempGenomeList);

	//Now that we've flattened our tree, total up our fitness value
	int longestPathLength = 0;
	int currentPathLength = 0;
	int currentPathIndex;
	int longestPathIndex;
	int currentDigit;

	for (int i = 0; i < length; i++) {
		currentDigit = *(int*)fullPools[i]->getIndex(fullIndexes[i]);
		currentPathIndex = i-currentPathLength;

		if (currentDigit == 1) {
			currentPathLength += 1;
		} else {
			if (currentPathLength > longestPathLength) {
				longestPathLength = currentPathLength;
				longestPathIndex = currentPathIndex;
			}
			currentPathLength = 0;
		}
	}

	free(fullPools);
	free(fullIndexes);

	if (currentPathLength > longestPathLength) {
		longestPathLength = currentPathLength;
		longestPathIndex = currentPathIndex;
	}

	Property<int> * storedProperty = new Property<int>(&longestPathIndex);

	returnProperties->setFitness(longestPathLength);
	returnProperties->addProperty(storedProperty);

	return returnProperties;
}

string HierLongestFragmentToString::toString(GeneNode ** pools, int * indexes, int genomeLength) {
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
