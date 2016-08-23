#include "nodes/EANode/mutations/AdaptiveRealValueMutation.hpp"
#include "core/utils/HierGC.hpp"
#include "loci/NumericSetLocus.hpp"
#include <math.h>
#include <limits>

AdaptiveRealValueMutation::AdaptiveRealValueMutation() {
	this->initialGenomeLength = 0;
	this->targetGenomeLength = 0;
	this->tausCalculated = false;
	this->stdDevLocus = NULL;
	this->setupDone = false;
}

Genome* AdaptiveRealValueMutation::mutate(Genome* initialGenome) {
	if (!this->setupDone) this->setupInternals(initialGenome);

	Genome* realInitial;
	if (
		this->targetGenomeLength == 0
		|| initialGenome->genomeLength() < this->targetGenomeLength
	) {
		realInitial = this->addStdDevs(initialGenome);
	} else {
		realInitial = new Genome(initialGenome);
	}

	Genome* mutated = this->mutateProper(realInitial);
	delete(realInitial);
	return mutated;
}

void AdaptiveRealValueMutation::setupInternals(Genome* firstTarget) {
	if (!this->tausCalculated) this->calculateTaus(firstTarget);
	if (!this->stdDevLocus) {
		this->stdDevLocus = new NumericSetLocus<double>(
			0,
			std::numeric_limits<double>::max()
		);
		HierGC::registerObject(this->stdDevLocus);
	}
	if (this->initialGenomeLength == 0) 
		this->calculateProperGenomeLengths(firstTarget);

	this->setupDone = true;
}

Gene* AdaptiveRealValueMutation::newLocusValue(Gene* current) {
	return NULL;
}

