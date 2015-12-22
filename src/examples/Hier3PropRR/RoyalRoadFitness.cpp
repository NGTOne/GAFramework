#include <sstream>
#include <string>
#include <libHierGA/HierGA.hpp>
#include "RoyalRoadFitness.hpp"

using namespace std;

string RoyalRoadToString::toString(GeneNode ** pools, int * indexes, int genomeLength) {
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
