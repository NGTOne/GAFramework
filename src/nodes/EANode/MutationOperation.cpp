//Abstract class for mutation operators. Lets us define any mutation operation we like.

#include <random>
#include <chrono>
#include <sstream>
#include "nodes/EANode/MutationOperation.hpp"

using namespace std;

MutationOperation::MutationOperation() {
	this->init(
		0,
		chrono::system_clock::now().time_since_epoch().count()
	);
}

MutationOperation::MutationOperation(double mutationRate) {
	this->init(
		mutationRate,
		chrono::system_clock::now().time_since_epoch().count()
	);
}

MutationOperation::MutationOperation(double mutationRate, unsigned int seed) {
	this->init(mutationRate, seed);
}

MutationOperation::~MutationOperation() {}

void MutationOperation::init(double mutationRate, unsigned int seed) {
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
	return new Genome(newGenome, loci, initialGenome->getSpeciesNode());
}

string MutationOperation::toString() {
	stringstream ss;

	ss << "Random seed: " << this->seed
		<< "\nMutation rate: " << this->mutationRate
		<< "\n";

	return ss.str();

}
