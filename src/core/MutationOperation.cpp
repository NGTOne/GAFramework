//Abstract class for mutation operators. Lets us define any mutation operation we like.

#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "core/MutationOperation.hpp"

using namespace std;

MutationOperation::MutationOperation() {
	seed = chrono::system_clock::now().time_since_epoch().count();
	init(0, seed);
}

MutationOperation::MutationOperation(double newMutationRate) {
	seed = chrono::system_clock::now().time_since_epoch().count();
	init(newMutationRate, seed);
}

MutationOperation::MutationOperation(double newMutationRate, unsigned newSeed) {
	init(newMutationRate, newSeed);
}

void MutationOperation::init(double newMutationRate, unsigned newSeed) {
	mutationRate = newMutationRate;
	seed = newSeed;
	mt19937 newGenerator(seed);
	generator = newGenerator;
}

Genome * MutationOperation::mutate(
	Genome * initialGenome,
	int * largestPossibleValues
) {
	int genomeLength = initialGenome->getGenomeLength();
	int * originalGenome = initialGenome->getGenome();

	double randomNumber;
	int * newGenome = (int*)malloc(sizeof(int)*genomeLength);
	uniform_real_distribution<double> mutationChanceDist(0.0, 1.0);

	for (int i = 0; i < genomeLength; i++) {
		randomNumber = mutationChanceDist(generator);

		if (randomNumber <= mutationRate) {
			newGenome[i] = getNewLocusValue(
				originalGenome[i],
				largestPossibleValues[i]
			);
		} else {
			newGenome[i] = originalGenome[i];
		}
	}

	Genome * newGene = new Genome(
		newGenome,
		genomeLength,
		initialGenome->getGeneNodes()
	);

	free(newGenome);

	return newGene;
}

string MutationOperation::toString() {
	string returnString = "";
	stringstream ss;

	ss << "Random seed: " << seed << "\nMutation rate: " << mutationRate << "\n";

	returnString = ss.str();

	return returnString;

}
