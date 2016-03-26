#include "loci/FloatLocus.hpp"

using namespace std;

template<> LibraryNode<float>::~LibraryNode() {}
template<> LibraryNode<float>::LibraryNode() {}
template<> string LibraryNode<float>::toString() {}

FloatLocus::FloatLocus(float bottom, float top, float resolution) {
	int size = (top - bottom)/resolution + 1;
	float * population = (float*)malloc(sizeof(float)*size);

	for (int i = 0; bottom + (i * resolution) <= top; i++) {
		population[i] = bottom + (i * resolution);
	}

	this->population = population;
	this->populationSize = size;
}

FloatLocus::FloatLocus(vector<float> values) {
	int size = values.size();
	float * population = (float*)malloc(sizeof(float)*size);

	for (int i = 0; i < size; i++) {
		population[i] = values[i];
	}

	this->population = population;
	this->populationSize = size;
}

FloatLocus::~FloatLocus() {
	free(this->population);
}

string FloatLocus::toString() {
	stringstream ss;

	for (int i = 0; i < populationSize; i++) {
		ss << population[i] << " ";
	}

	ss << "\nRandom Seed: " << seed << "\n";

	return ss.str();
}

template <> float * LibraryNode<float>::getIndex(int index) {
	return &population[index];
}

// Legacy garbage
template<> void LibraryNode<float>::setFitnessAtIndex(int, int) {}
template<> void LibraryNode<float>::propagateFitnesses() {}
template<> int LibraryNode<float>::getFitnessAtIndex(int) {}
