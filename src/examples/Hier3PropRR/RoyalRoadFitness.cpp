#include <sstream>
#include <string>
#include <libGAFramework/GAFramework.hpp>
#include "RoyalRoadFitness.hpp"

using namespace std;

string RoyalRoadToString::toString(GenePool ** pools, int * indexes, int genomeLength) {
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
