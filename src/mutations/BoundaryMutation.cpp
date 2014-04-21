#include "BoundaryMutation.h"
#include <chrono>
#include <random>

using namespace std;

BoundaryMutation::BoundaryMutation() : MutationOperation() {}
BoundaryMutation::BoundaryMutation(double newMutationRate) : MutationOperation(newMutationRate) {}
BoundaryMutation::BoundaryMutation(double newMutationRate, unsigned newSeed) : MutationOperation(newMutationRate, newSeed) {}


int * BoundaryMutation::mutate(int * initialGenome, int * largestPossibleValues, int genomeLength) {
	double randomNumber;
	int * newGenome = (int*)malloc(sizeof(int)*genomeLength);

	uniform_real_distribution<double> mutationChanceDistribution(0.0, 1.0);
	uniform_int_distribution<int> newValueDistribution(0, 1);

	for (int i = 0; i < genomeLength; i++) {
		randomNumber = mutationChanceDistribution(generator);

		if (randomNumber <= mutationRate) {
			int newValue = newValueDistribution(generator);

			if (newValue == 0) {
				newGenome[i] = 0;
			} else {
				newGenome[i] = largestPossibleValues[i];
			}
		} else {
			newGenome[i] = initialGenome[i];
		}
	}

	return newGenome;
}
