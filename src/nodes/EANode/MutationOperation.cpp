//Abstract class for mutation operators. Lets us define any mutation operation we like.

#include <random>
#include <chrono>
#include <sstream>
#include "nodes/EANode/MutationOperation.hpp"

using namespace std;

MutationOperation::MutationOperation() {
	seed = chrono::system_clock::now().time_since_epoch().count();
	this->init(0, seed);
}

MutationOperation::MutationOperation(double mutationRate) {
	seed = chrono::system_clock::now().time_since_epoch().count();
	this->init(mutationRate, seed);
}

MutationOperation::MutationOperation(double mutationRate, unsigned seed) {
	this->init(mutationRate, seed);
}

void MutationOperation::init(double mutationRate, unsigned seed) {
	this->mutationRate = mutationRate;
	this->seed = seed;
	this->generator = mt19937(seed);
}

Genome * MutationOperation::mutate(Genome * initialGenome) {
	vector<unsigned int> newGenome;
	vector<unsigned int> existingGenome = initialGenome->getGenome();
	vector<Locus*> loci = initialGenome->getLoci();
	uniform_real_distribution<double> mutationDist(0, 1);

	for (unsigned int i = 0; i < initialGenome->genomeLength(); i++)
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
	return new Genome(newGenome, loci);
}

string MutationOperation::toString() {
	stringstream ss;

	ss << "Random seed: " << seed
		<< "\nMutation rate: " << mutationRate
		<< "\n";

	return ss.str();

}
