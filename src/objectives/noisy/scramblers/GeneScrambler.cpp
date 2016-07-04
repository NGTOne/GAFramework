#include "objectives/noisy/scramblers/GeneScrambler.hpp"

GeneScrambler::GeneScrambler() {
	this->mutator = NULL;
}

GeneScrambler::GeneScrambler(MutationOperation * mutator) {
	this->mutator = mutator;
}

GeneScrambler::~GeneScrambler() {
	delete(this->mutator);
}

Genome GeneScrambler::scramble(Genome * target) {
	return Genome(
		this->mutator->mutate(target->getTemplate()),
		target->getSpeciesNode()
	);
}

Genome GeneScrambler::scramble(Genome target) {
	return this->scramble(&target);
}
