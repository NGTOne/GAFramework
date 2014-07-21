#include <sstream>
#include <string>
#include <libGAFramework/GAFramework.hpp>
#include "HierRoyalRoadFitness.hpp"

using namespace std;

HierRoyalRoadFitness::HierRoyalRoadFitness() : FitnessFunction() {}

PropertiesList * HierRoyalRoadFitness::checkFitness(GenePool ** pools, int * indexes, int genomeLength) {
	Individual * tempIndividual;
	PropertiesList * returnProperties = new PropertiesList(0);
	PropertiesList * tempProperties;
	Property<int> ** tempPropertiesList;

	int ** allPathLengths = (int**)malloc(sizeof(int*)*genomeLength);
	int ** allPathIndexes = (int**)malloc(sizeof(int*)*genomeLength);
	int numPathsPerGenome[genomeLength];

	int tempPropertiesLength;

	int * tempPathLengths;
	int * tempPathIndexes;

	int currentTempPath = 0;
	int lowGenomeLength;

	int numPaths = 0;
	int numPathsListed = 0;

	for (int i = 0; i < genomeLength; i++) {
		tempIndividual = (Individual*)pools[i]->getIndex(indexes[i]);
		
		tempProperties = tempIndividual->getProperties();

		tempPropertiesLength = tempProperties->getNumProperties();
		tempPropertiesList = (Property<int>**)tempProperties->getProperties();

		lowGenomeLength = *(tempPropertiesList[0]->getProperty());

		tempPathLengths = (int*)malloc(sizeof(int)*((tempPropertiesLength)/2));
		tempPathIndexes = (int*)malloc(sizeof(int)*((tempPropertiesLength)/2));

		//Read the list of paths out of the property list
		currentTempPath = 0;
		for (int k = 1; k < tempPropertiesLength;) {
			tempPathLengths[currentTempPath] = *(tempPropertiesList[k++]->getProperty());
			tempPathIndexes[currentTempPath++] = *(tempPropertiesList[k++]->getProperty());
			numPaths++;
		}

		allPathLengths[i] = tempPathLengths;
		allPathIndexes[i] = tempPathIndexes;
		numPathsPerGenome[i] = currentTempPath;
	}

	if (numPaths == 0) {
		returnProperties->setFitness(0);
		
		int newLength = genomeLength*lowGenomeLength;
		PropertyBase * newProperty = new Property<int>(&newLength);
		returnProperties->addProperty(newProperty);

		return returnProperties;
	}

	tempPathLengths = (int*)malloc(sizeof(int)*numPaths);
	tempPathIndexes = (int*)malloc(sizeof(int)*numPaths);

	//Move them into one long list, and adjust for position in the overall
	//array
	for (int i = 0; i < genomeLength; i++) {
		for (int k = 0; k < numPathsPerGenome[i]; k++) {
			tempPathLengths[numPathsListed] = allPathLengths[i][k];
			tempPathIndexes[numPathsListed++] = allPathIndexes[i][k] + (lowGenomeLength*i);
		}
	}

	int numConsolidatedPaths = 0;
	int * newPathLengths = (int*)malloc(sizeof(int));
	int * newPathIndexes = (int*)malloc(sizeof(int));

	int currentPathIndex = tempPathIndexes[0];
	int currentPathLength = tempPathLengths[0];

	int tempPathLength;
	int tempPathIndex;

	for (int i = 1; i < numPaths; i++) {
		tempPathIndex = tempPathIndexes[i];
		tempPathLength = tempPathLengths[i];

		if (currentPathIndex + currentPathLength == tempPathIndex) {
			currentPathLength += tempPathLength;
		} else {
			newPathLengths = (int*)realloc(newPathLengths, sizeof(int)*(numConsolidatedPaths+1));
			newPathIndexes = (int*)realloc(newPathIndexes, sizeof(int)*(numConsolidatedPaths+1));
			newPathLengths[numConsolidatedPaths] = currentPathLength;
			newPathIndexes[numConsolidatedPaths] = currentPathIndex;
			currentPathIndex = tempPathIndex;
			currentPathLength = tempPathLength;
			numConsolidatedPaths += 1;
		}
	}

	newPathLengths = (int*)realloc(newPathLengths, sizeof(int)*(numConsolidatedPaths+1));
	newPathIndexes = (int*)realloc(newPathIndexes, sizeof(int)*(numConsolidatedPaths+1));
	newPathLengths[numConsolidatedPaths] = currentPathLength;               
	newPathIndexes[numConsolidatedPaths] = currentPathIndex;
	numConsolidatedPaths++;

	int longestPathLength = 0;

	for (int i = 0; i < numConsolidatedPaths; i++) {
		if (newPathLengths[i] > longestPathLength) {
			longestPathLength = newPathLengths[i];
		}
	}

	returnProperties->setFitness(longestPathLength);
	
	int newLength = genomeLength*lowGenomeLength;

	PropertyBase * newProperty = new Property<int>(&newLength);
        returnProperties->addProperty(newProperty);

	int currentProperty = 0;

        for (int i = 0; i < numConsolidatedPaths; i++) {
		newProperty = new Property<int>(&newPathLengths[currentProperty]);
		returnProperties->addProperty(newProperty);

		newProperty = new Property<int>(&newPathIndexes[currentProperty++]);
		returnProperties->addProperty(newProperty);
        }

	free(newPathLengths);
	free(newPathIndexes);

	for (int i = 0; i < genomeLength; i++) {
		free(allPathLengths[i]);
		free(allPathIndexes[i]);
	}

	free(allPathLengths);
	free(allPathIndexes);
	free(tempPathLengths);
	free(tempPathIndexes);

	return returnProperties;
}

string HierRoyalRoadToString::toString(GenePool ** pools, int * indexes, int genomeLength) {
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
