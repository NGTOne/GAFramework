#include "core/meta/MetaPopulationObjective.hpp"
#include "core/meta/BlanketResolver.hpp"

MetaPopulationObjective::MetaPopulationObjective(
	ObjectiveFunction* flattenedObjective
) : NestedObjective(flattenedObjective) {}

Fitness MetaPopulationObjective::checkFitness(Genome* genome) {
	Genome resolved = BlanketResolver::resolveBlanket(genome);
	return this->checkInnerFitness(&resolved);
}
