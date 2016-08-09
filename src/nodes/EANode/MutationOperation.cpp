#include <random>
#include <chrono>
#include <sstream>
#include "nodes/EANode/MutationOperation.hpp"
#include "core/HierRNG.hpp"

using namespace std;

MutationOperation::MutationOperation() {
	this->init(0);
}

MutationOperation::MutationOperation(double mutationRate) {
	this->init(mutationRate);
}

MutationOperation::~MutationOperation() {}

void MutationOperation::init(double mutationRate) {
	this->mutationRate = mutationRate;
}

Genome* MutationOperation::mutate(Genome* initialGenome) {
	return new Genome(
		this->mutate(initialGenome->getTemplate()),
		initialGenome->getSpeciesNode()
	);
}

GenomeTemplate MutationOperation::mutate(GenomeTemplate initial) {
	std::vector<Gene*> newGenome;

	for (unsigned int i = 0; i < initial.genomeLength(); i++)
		newGenome.push_back(
			HierRNG::zeroOne<double>() < this->mutationRate
				? this->newLocusValue(initial.getGene(i))
				: initial.getGene(i)
		);

	return GenomeTemplate(newGenome);
}

string MutationOperation::toString() {
	stringstream ss;
	ss << "\nMutation rate: " << this->mutationRate << "\n";
	return ss.str();
}
