#include "UniformMutation.h"
#include <chrono>
#include <random>

using namespace std;

UniformMutation::UniformMutation() : MutationOperation() {}
UniformMutation::UniformMutation(double newMutationRate) : MutationOperation(newMutationRate) {}
UniformMutation::UniformMutation(double newMutationRate, unsigned newSeed) : MutationOperation(newMutationRate, newSeed) {}


Genome * UniformMutation::mutate(Genome * initialGenome, int * largestPossibleValues) {
	int genomeLength = initialGenome->getGenomeLength();
	int * originalGenome = initialGenome->getGenome();

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
			newGenome[i] = originalGenome[i];
		}
	}

	Genome * newGene = new Genome(newGenome, genomeLength, initialGenome->getGenePools());

	free(newGenome);

	return newGene;
}
