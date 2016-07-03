#include "objectives/noisy/scramblers/GeneScrambler.hpp"

GeneScrambler::GeneScrambler(MutationOperation * mutator) {
	this->mutator = mutator;
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
