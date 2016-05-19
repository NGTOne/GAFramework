#include "systems/AccelSSGA.hpp"

AccelSSGA::AccelSSGA(SelectionStrategy * strategy) : SSGA(strategy) {}

AccelSSGA::AccelSSGA(
	SelectionStrategy * strategy,
	unsigned seed
) : SSGA(strategy, seed) {}

AccelSSGA::AccelSSGA(
	SelectionStrategy * strategy,
	NichingStrategy * niching
) : SSGA(strategy, niching) {}

AccelSSGA::AccelSSGA(
	SelectionStrategy * strategy,
	NichingStrategy * niching,
	unsigned seed
) : SSGA(strategy, niching, seed) {}

std::vector<Genome*> AccelSSGA::breedMutateSelect(
	std::vector<Genome*> initialPopulation,
	std::vector<int> & populationFitnesses,
	CrossoverOperation * cross,
	MutationOperation * mutation,
	std::vector<ObjectiveFunction*> objectives
) {
	std::vector<Genome*> newPopulation;
	for (int i = 0; i < initialPopulation.size()/2; i++) {
		newPopulation = SSGA::breedMutateSelect(
			initialPopulation,
			populationFitnesses,
			cross,
			mutation,
			objectives
		);
	}

	return newPopulation;
}
