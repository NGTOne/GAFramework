#include <sstream>
#include <string>
#include "RoyalRoadFitness.h"
#include "NonHierarchicalGenePool.h"

using namespace std;

RoyalRoadFitness::RoyalRoadFitness() : FitnessFunction() {}

int * RoyalRoadFitness::checkFitness(GenePool ** pools, int * indexes, int genomeLength) {
	int longestPathLength = 0;
	int currentPathLength = 0;
	int currentPathIndex;
	int longestPathIndex;
	int currentDigit;
	int * returnProperties = (int*)malloc(sizeof(int)*3);

	for (int i = 0; i < genomeLength; i++) {
		currentDigit = *(int*)pools[i]->getIndex(indexes[i]);
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

	if (currentPathLength > longestPathLength) {
		longestPathLength = currentPathLength;
		longestPathIndex = currentPathIndex;
	}

	returnProperties[0] = 2;
	returnProperties[1] = longestPathLength;
	returnProperties[2] = longestPathIndex;

	return returnProperties;
}

string RoyalRoadFitness::toString(GenePool ** pools, int * indexes, int genomeLength) {
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
