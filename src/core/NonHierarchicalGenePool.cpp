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

	ss << "Population: ";

	for (int i = 0; i < populationSize; i++) {
		ss << myPopulation[i] << " ";
	}

	ss << "\nRandom Seed: " << seed << "\n";

	returnString = ss.str();

	return returnString;
}

template <> void * NonHierarchicalGenePool<double>::getIndex(int index) {
	double * returnValue = &myPopulation[index];

	return (void*)returnValue;
}

template <> string NonHierarchicalGenePool<double>::toString() {
	string returnString = "";
	stringstream ss;

	ss << "Population: ";

	for (int i = 0; i < populationSize; i++) {
		ss << myPopulation[i] << " ";
	}

	ss << "\nRandom Seed: " << seed << "\n";

	returnString = ss.str();

	return returnString;
}

template <> void * NonHierarchicalGenePool<char>::getIndex(int index) {
	char * returnValue = &myPopulation[index];

	return (void*)returnValue;
}

template <> string NonHierarchicalGenePool<char>::toString() {
	string returnString = "";
	stringstream ss;

	ss << "Population: ";

	for (int i = 0; i < populationSize; i++) {
		ss << myPopulation[i] << " ";
	}

	ss << "\nRandom Seed: " << seed << "\n";

	returnString = ss.str();

	return returnString;
}

template <> void * NonHierarchicalGenePool<bool>::getIndex(int index) {
	bool * returnValue = &myPopulation[index];

	return (void*)returnValue;
}

template <> string NonHierarchicalGenePool<bool>::toString() {
	string returnString = "";
	stringstream ss;

	ss << "Population: ";

	for (int i = 0; i < populationSize; i++) {
		ss << myPopulation[i] << " ";
	}

	ss << "\nRandom Seed: " << seed << "\n";

	returnString = ss.str();

	return returnString;
}
