#include <random>
#include <chrono>
#include "UniformCrossover.h"

using namespace std;

UniformCrossover::UniformCrossover(double crossoverChance) : CrossoverOperation() {
	crossoverRate = crossoverChance;
}

UniformCrossover::UniformCrossover(double crossoverChance, unsigned newSeed) : CrossoverOperation(newSeed) {
	crossoverRate = crossoverChance;
}

int ** UniformCrossover::crossOver(int firstGenome[], int secondGenome[], int firstGenomeLength, int secondGenomeLength) {

	//If our parents are of different types, we're gonna have a problem
	if (firstGenomeLength != secondGenomeLength) {
		return NULL;
	}

	//We're generating two children - each one uses the same crossover
	//points, but draws from the parents in a different order
	int ** children = (int**)malloc(sizeof(int*)*2);

	children[0] = (int*)malloc(sizeof(int)*firstGenomeLength);
	children[1] = (int*)malloc(sizeof(int)*secondGenomeLength);

	uniform_real_distribution<double> distribution(0, 1);

	for (int i = 0; i < firstGenomeLength; i++) {
		if (distribution(generator) <= crossoverRate) {
			children[0][i] = secondGenome[i];
			children[1][i] = firstGenome[i];
		} else {
			children[0][i] = firstGenome[i];
			children[1][i] = secondGenome[i];
		}
	}

	return children;
}
