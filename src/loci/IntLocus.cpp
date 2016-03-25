#include "loci/IntLocus.hpp"

using namespace std;

template<> LibraryNode<int>::~LibraryNode() {}
template<> LibraryNode<int>::LibraryNode() {}
template<> string LibraryNode<int>::toString() {}

IntLocus::IntLocus(int bottom, int top) {
	int size = (top - bottom) + 1;
	int * population = (int*)malloc(sizeof(int)*size);

	for (int i = bottom; i <= top; i++) {
		population[i-bottom] = i;
	}

	this->population = population;
	this->populationSize = size;
}

IntLocus::IntLocus(vector<int> values) {
	int size = values.size();
	int * population = (int*)malloc(sizeof(int)*size);

	for (int i = 0; i < size; i++) {
		population[i] = values[i];
	}

	this->population = population;
	this->populationSize = size;
}

IntLocus::~IntLocus() {
	free(this->population);
}

string IntLocus::toString() {
	stringstream ss;

	for (int i = 0; i < populationSize; i++) {
		ss << population[i] << " ";
	}

	ss << "\nRandom Seed: " << seed << "\n";

	return ss.str();
}

template <> int * LibraryNode<int>::getIndex(int index) {
	return &population[index];
}

// Legacy garbage
template<> void LibraryNode<int>::setFitnessAtIndex(int, int) {}
template<> void LibraryNode<int>::propagateFitnesses() {}
template<> int LibraryNode<int>::getFitnessAtIndex(int) {}
