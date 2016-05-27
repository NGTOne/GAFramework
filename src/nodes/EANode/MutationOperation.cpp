//Abstract class for mutation operators. Lets us define any mutation operation we like.

#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "nodes/EANode/MutationOperation.hpp"

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
	generator = mt19937(seed);
}

Genome * MutationOperation::mutate(Genome * initialGenome) {
	vector<int> newGenome, existingGenome = initialGenome->getGenome();
	vector<Locus*> loci = initialGenome->getLoci();
	uniform_real_distribution<double> mutationDist(0, 1);
	for (int i = 0; i < initialGenome->genomeLength(); i++) {
		if (mutationDist(this->generator) < this->mutationRate) {
			newGenome.push_back(
				this->getNewLocusValue(
					existingGenome[i],
					loci[i]->topIndex()
				)
			);
		} else {
			newGenome.push_back(existingGenome[i]);
		}
	}
	return new Genome(newGenome, loci);
}

string MutationOperation::toString() {
	string returnString = "";
	stringstream ss;

	ss << "Random seed: " << seed << "\nMutation rate: " << mutationRate << "\n";

	returnString = ss.str();

	return returnString;

}
