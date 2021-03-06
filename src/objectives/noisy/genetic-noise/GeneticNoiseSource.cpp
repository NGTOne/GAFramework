#include "objectives/noisy/genetic-noise/GeneticNoiseSource.hpp"
#include "core/utils/HierGC.hpp"

GeneticNoiseSource::GeneticNoiseSource() {
	this->mutator = NULL;
}

GeneticNoiseSource::GeneticNoiseSource(MutationOperation * mutator) {
	this->mutator = mutator;
}

GeneticNoiseSource::~GeneticNoiseSource() {}

void GeneticNoiseSource::registerInternalObjects() {
	HierGC::registerObject(this->mutator);
}

Genome GeneticNoiseSource::addNoise(Genome * target) {
	return Genome(
		this->mutator->mutate(target->getTemplate()),
		target->getSpeciesNode()
	);
}

Genome GeneticNoiseSource::addNoise(Genome target) {
	return this->addNoise(&target);
}
