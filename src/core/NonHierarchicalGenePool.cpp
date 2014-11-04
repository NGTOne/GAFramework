//This is a gene pool type that takes basic "literal" types for its genome
//elements - lets us build "classical" GAs
//It has no generational mechanics, selection strategy, or fitness evaluations,
//which means it's distinct from the HierarchicalGenePool

using namespace std;

#include <sstream>
#include <string>
#include "core/NonHierarchicalGenePool.hpp"

template <> void * NonHierarchicalGenePool<int>::getIndex(int index) {
	int * returnValue = &myPopulation[index];

	return (void*)returnValue;
}

template <> string NonHierarchicalGenePool<int>::toString() {
	string returnString = "";
	stringstream ss;

	for (int i = 0; i < populationSize; i++) {
		ss << myPopulation[i] << " ";
	}

	returnString = ss.str();

	return returnString;
}
