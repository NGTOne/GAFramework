#include <sstream>
#include <string>
#include <libGAFramework/GAFramework.hpp>
#include "HierRoyalRoadFitness.hpp"

using namespace std;

HierRoyalRoadFitness::HierRoyalRoadFitness() : FitnessFunction() {}

int * HierRoyalRoadFitness::checkFitness(GenePool ** pools, int * indexes, int genomeLength) {
	Individual * tempIndividual;
	int * returnProperties = (int*)malloc(sizeof(int)*3);
	int * tempProperties;

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

		tempPropertiesLength = tempProperties[0];

		lowGenomeLength = tempProperties[2];

		tempPathLengths = (int*)malloc(sizeof(int)*((tempPropertiesLength-3)/2));
		tempPathIndexes = (int*)malloc(sizeof(int)*((tempPropertiesLength-3)/2));

		//Read the list of paths out of the property list
		currentTempPath = 0;
		for (int k = 3; k < tempPropertiesLength;) {
			tempPathLengths[currentTempPath] = tempProperties[k++];
			tempPathIndexes[currentTempPath++] = tempProperties[k++];
			numPaths++;
		}

		allPathLengths[i] = tempPathLengths;
		allPathIndexes[i] = tempPathIndexes;
		numPathsPerGenome[i] = currentTempPath;
	}

	if (numPaths == 0) {
	        returnProperties[0] = 3;
	        returnProperties[1] = 0;
        	returnProperties[2] = genomeLength*lowGenomeLength;

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

        returnProperties[0] = 3 + numConsolidatedPaths*2;
        returnProperties[1] = longestPathLength;
        returnProperties[2] = genomeLength*lowGenomeLength;

        returnProperties = (int*)realloc(returnProperties, sizeof(int)*(3+(numConsolidatedPaths*2)));

	int currentProperty = 0;

        for (int i = 3; i < 3 + numConsolidatedPaths*2;) {
                returnProperties[i++] = newPathLengths[currentProperty];
                returnProperties[i++] = newPathIndexes[currentProperty++];
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

string HierRoyalRoadFitness::toString(GenePool ** pools, int * indexes, int genomeLength) {
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
