#include <sstream>
#include <string>
#include "RoyalRoadFitness.h"
#include "NonHierarchicalGenePool.h"

using namespace std;

RoyalRoadFitness::RoyalRoadFitness() : FitnessFunction() {}

//Slightly more complex than the base RR fitness - returns the location of
//EVERY path, not just the longest one
int * RoyalRoadFitness::checkFitness(GenePool ** pools, int * indexes, int genomeLength) {
	int longestPathLength = 0;
	int currentPathLength = 0;
	int currentPathIndex;
	int currentDigit;
	int * returnProperties = (int*)malloc(sizeof(int)*3);
	int pathLengths[genomeLength/2];
	int pathIndexes[genomeLength/2];
	int currentPath = 0;
	int currentProperty = 0;

	for (int i = 0; i < genomeLength; i++) {
		currentDigit = *(int*)pools[i]->getIndex(indexes[i]);
		currentPathIndex = i-currentPathLength;

		if (currentDigit == 1) {
			currentPathLength += 1;
		} else {
			if (currentPathLength > 0) {
	                        pathLengths[currentPath] = currentPathLength;
	                        pathIndexes[currentPath] = currentPathIndex;
        	                currentPath++;
                	        currentPathLength = 0;
			}
		}
	}

	if (currentPathLength > 0) {
		pathLengths[currentPath] = currentPathLength;
                pathIndexes[currentPath] = currentPathIndex;
                currentPath++;
                currentPathLength = 0;
        }


	for (int i = 0; i < currentPath; i++) {
		if (pathLengths[i] > longestPathLength) {
			longestPathLength = pathLengths[i];
		}
	}

	returnProperties[0] = 3 + currentPath*2;
	returnProperties[1] = longestPathLength;
	returnProperties[2] = genomeLength;

	returnProperties = (int*)realloc(returnProperties, sizeof(int)*(3+(currentPath*2)));

	for (int i = 3; i < 3 + currentPath*2;) {
		returnProperties[i++] = pathLengths[currentProperty];
		returnProperties[i++] = pathIndexes[currentProperty++];
	}

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
