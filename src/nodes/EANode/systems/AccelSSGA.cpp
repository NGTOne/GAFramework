#include "nodes/EANode/systems/AccelSSGA.hpp"

AccelSSGA::AccelSSGA(
	SelectionStrategy* strategy,
	CrossoverOperation* cross,
	MutationOperation* mutation
) : SSGA(strategy, cross, mutation) {}

AccelSSGA::AccelSSGA(
	SelectionStrategy* strategy,
	CrossoverOperation* cross,
	MutationOperation* mutation,
	NichingStrategy* niching
) : SSGA(strategy, cross, mutation, niching) {}

std::vector<Genome*> AccelSSGA::breedMutateSelect(
	std::vector<Genome*> initialPopulation,
	std::vector<Fitness>& populationFitnesses,
	std::vector<ObjectiveFunction*> objectives,
	std::string speciesNode
) {
	std::vector<Genome*> newPopulation;
	for (unsigned int i = 0; i < initialPopulation.size(); i++)
		newPopulation.push_back(new Genome(initialPopulation[i]));

	for (unsigned int i = 0; i < initialPopulation.size()/2; i++) {
		std::vector<Genome*> tempPopulation = SSGA::breedMutateSelect(
			newPopulation,
			populationFitnesses,
			objectives,
			speciesNode
		);

		for (unsigned int k = 0; k < newPopulation.size(); k++)
			delete(newPopulation[k]);
		newPopulation = tempPopulation;
	}

	return newPopulation;
}
