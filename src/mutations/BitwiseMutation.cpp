#include "BitwiseMutation.h"
#include <chrono>
#include <random>

using namespace std;

BitwiseMutation::BitwiseMutation() : MutationOperation() {}
BitwiseMutation::BitwiseMutation(double newMutationRate) : MutationOperation(newMutationRate) {}
BitwiseMutation::BitwiseMutation(double newMutationRate, unsigned newSeed) : MutationOperation(newMutationRate, newSeed) {}


int * BitwiseMutation::mutate(int * initialGenome, int * largestPossibleValues, int genomeLength) {
	double randomNumber;
	int * newGenome = (int*)malloc(sizeof(int)*genomeLength);

	uniform_real_distribution<double> mutationChanceDistribution(0.0, 1.0);

	for (int i = 0; i < genomeLength; i++) {
		randomNumber = mutationChanceDistribution(generator);

		if (randomNumber <= mutationRate) {
			//Due to the chosen representational model, each gene
			//in the genome might have a different maximum
			//value - hence, this is necessary
	                uniform_int_distribution<int> newValueDistribution(0, largestPossibleValues[i]);

			newGenome[i] = newValueDistribution(generator);
		} else {
			newGenome[i] = initialGenome[i];
		}
	}

	return newGenome;
}
