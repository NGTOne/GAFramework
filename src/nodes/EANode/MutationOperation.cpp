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
	return new Genome(
		this->mutate(initialGenome->getTemplate()),
		initialGenome->getSpeciesNode()
	);
}

unsigned int MutationOperation::getNewLocusValue(
	std::tuple<unsigned int, Locus*> existing
) {
	return this->getNewLocusValue(
		std::get<0>(existing),
		std::get<1>(existing)->topIndex()
	);
}

GenomeTemplate MutationOperation::mutate(GenomeTemplate initial) {
	std::vector<unsigned int> newGenome;
	uniform_real_distribution<double> mutationDist(0, 1);

	for (unsigned int i = 0; i < initial.genomeLength(); i++)
		if (mutationDist(this->generator) < this->mutationRate) {
			newGenome.push_back(
				this->getNewLocusValue(initial.getIndex(i))
			);
		} else {
			newGenome.push_back(initial.getGene(i));
		}

	return GenomeTemplate(newGenome, initial.getLoci());
}

string MutationOperation::toString() {
	stringstream ss;

	ss << "Random seed: " << this->seed
		<< "\nMutation rate: " << this->mutationRate
		<< "\n";

	return ss.str();

}
