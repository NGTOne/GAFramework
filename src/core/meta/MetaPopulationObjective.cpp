#include "core/meta/MetaPopulationObjective.hpp"
#include "core/meta/BlanketResolver.hpp"

MetaPopulationObjective::MetaPopulationObjective(
	ObjectiveFunction * flattenedObjective
) {
	this->flattenedObjective = flattenedObjective;
}

int MetaPopulationObjective::checkFitness(Genome * genome) {
	Genome resolved = BlanketResolver::resolveBlanket(genome);
	return this->flattenedObjective->checkFitness(&resolved);
}
