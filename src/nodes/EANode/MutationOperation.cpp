#include <random>
#include <chrono>
#include <sstream>
#include "nodes/EANode/MutationOperation.hpp"
#include "core/utils/HierRNG.hpp"

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
	GenomeTemplate initial = initialGenome->getTemplate();
	GenomeTemplate result = this->mutate(initial);
	Genome* resultGenome = new Genome(
		result,
		initialGenome->getSpeciesNode()
	);
	return resultGenome;
}

GenomeTemplate MutationOperation::mutate(GenomeTemplate initial) {
	std::vector<Gene*> newGenome;

	for (unsigned int i = 0; i < initial.genomeLength(); i++)
		newGenome.push_back(HierRNG::chooseWithProb(
			this->mutationRate,
			this->newLocusValue(initial.getGene(i)),
			initial.getGene(i)->copy()
		));

	GenomeTemplate result(newGenome);
	for (unsigned int i = 0; i < newGenome.size(); i++)
		delete(newGenome[i]);

	return result;
}

std::string MutationOperation::toString() {
	std::stringstream ss;
	ss << "\nMutation rate: " << this->mutationRate << "\n";
	return ss.str();
}
