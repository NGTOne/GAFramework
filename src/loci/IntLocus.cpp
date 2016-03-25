#include "loci/IntLocus.hpp"

using namespace std;

IntLocus::IntLocus(int bottom, int top) {
	int * population = (int*)malloc(sizeof(int)*((top-bottom)+1));

	for (int i = bottom; i <= top; i++) {
		population[i-bottom] = i;
	}

	this->population = population;
	this->populationSize = top-bottom;
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

template <> int * LibraryNode<int>::getIndex(int index) {
	return &population[index];
}
