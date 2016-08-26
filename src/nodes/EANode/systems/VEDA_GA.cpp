#include "nodes/EANode/systems/VEDA_GA.hpp"
#include "nodes/EANode/mutations/VEDAMutation.hpp"

VEDA_GA::VEDA_GA(
	unsigned int numElites,
	bool randomElitePlacement,
	SelectionStrategy* strategy,
	CrossoverOperation* cross
) : GA(numElites, randomElitePlacement, strategy, cross, new VEDAMutation()) {}

VEDA_GA::VEDA_GA(
	unsigned int numElites,
	SelectionStrategy* strategy,
	CrossoverOperation* cross
) : GA(numElites, strategy, cross, new VEDAMutation()) {}

std::vector<Genome*> VEDA_GA::breedMutateSelect(
	std::vector<Genome*> initialPopulation,
	std::vector<float>& populationFitnesses,
	std::vector<ObjectiveFunction*> objectives,
	std::string speciesNode
) {
	((VEDAMutation*)this->mutation)->setLambda(initialPopulation.size());
	((VEDAMutation*)this->mutation)->setMu(initialPopulation.size());
	((VEDAMutation*)this->mutation)->calculateAverages(initialPopulation);

	return GA::breedMutateSelect(
		initialPopulation,
		populationFitnesses,
		objectives,
		speciesNode
	);
}
