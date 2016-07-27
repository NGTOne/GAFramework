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

void MutationOperation::registerInternalObjects(
	NodeGarbageCollector & collector
) {}

void MutationOperation::init(double mutationRate) {
	this->mutationRate = mutationRate;
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

	for (unsigned int i = 0; i < initial.genomeLength(); i++)
		if (HierRNG::zeroOne<double>() < this->mutationRate) {
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
	ss << "\nMutation rate: " << this->mutationRate << "\n";
	return ss.str();
}
