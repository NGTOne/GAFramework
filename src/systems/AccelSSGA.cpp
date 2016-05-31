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
	for (unsigned int i = 0; i < initialPopulation.size(); i++)
		newPopulation.push_back(new Genome(initialPopulation[i]));

	for (unsigned int i = 0; i < initialPopulation.size()/2; i++) {
		std::vector<Genome*> tempPopulation = SSGA::breedMutateSelect(
			newPopulation,
			populationFitnesses,
			cross,
			mutation,
			objectives
		);

		for (unsigned int k = 0; k < newPopulation.size(); k++)
			delete(newPopulation[k]);
		newPopulation = tempPopulation;
	}

	return newPopulation;
}
