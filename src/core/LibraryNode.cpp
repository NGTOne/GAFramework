using namespace std;

#include <sstream>
#include <string>
#include "core/LibraryNode.hpp"

template <> void * LibraryNode<int>::getIndex(int index) {
	int * returnValue = &myPopulation[index];

	return (void*)returnValue;
}

template <> string LibraryNode<int>::toString() {
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

template <> void * LibraryNode<double>::getIndex(int index) {
	double * returnValue = &myPopulation[index];

	return (void*)returnValue;
}

template <> string LibraryNode<double>::toString() {
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

template <> void * LibraryNode<char>::getIndex(int index) {
	char * returnValue = &myPopulation[index];

	return (void*)returnValue;
}

template <> string LibraryNode<char>::toString() {
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

template <> void * LibraryNode<bool>::getIndex(int index) {
	bool * returnValue = &myPopulation[index];

	return (void*)returnValue;
}

template <> string LibraryNode<bool>::toString() {
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

template <> void * LibraryNode<string>::getIndex(int index) {
	string * returnValue = &myPopulation[index];

	return (void*)returnValue;
}

template <> string LibraryNode<string>::toString() {
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
