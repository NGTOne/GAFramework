#include "BitwiseMutation.h"
#include <chrono>
#include <random>

using namespace std;

int * BitwiseMutation::mutate(int initialGenome[], int largestPossibleValues[], int genomeLength) {
	int randomNumber;
	int * newGenome = (int*)malloc(sizeof(int)*genomeLength);

	mt19937 generator(seed);
	uniform_real_distribution<double> mutationChanceDistribution(0, 1);

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
