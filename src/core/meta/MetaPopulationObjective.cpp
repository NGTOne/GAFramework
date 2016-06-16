#include "core/meta/MetaPopulationObjective.hpp"

MetaPopulationObjective::MetaPopulationObjective(
	ObjectiveFunction * flattenedObjective
) {
	this->flattenedObjective = flattenedObjective;
}

int MetaPopulationObjective::checkFitness(Genome * genome) {
	Genome resolved = this->resolveBlanket(genome);
	return this->flattenedObjective->checkFitness(&resolved);
}
