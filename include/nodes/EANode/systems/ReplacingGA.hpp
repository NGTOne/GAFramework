#include "../EvolutionarySystem.hpp"
#include <string>
#pragma once

/*
* The ReplacingGA model represents a "classical" GA model,
* similar to that proposed by John Holland in the 1970s, but where the
* offspring may (or may not) replace their parents at the exact same locations
* in the population.
*/

class ReplacingGA : public EvolutionarySystem {
	private:

	protected:
	void removeUnusedIndividuals(
		std::vector<Genome*> initialPopulation,
		std::vector<Genome*> newPopulation
	);

	bool inPopulation(
		Genome * target,
		std::vector<Genome*> population
	);

	public:
	ReplacingGA(
		SelectionStrategy * strategy,
		CrossoverOperation * cross,
		MutationOperation * mutation
	);
	ReplacingGA(
		SelectionStrategy * strategy,
		CrossoverOperation * cross,
		MutationOperation * mutation,
		unsigned int seed
	);

	virtual std::vector<Genome*> breedMutateSelect(
		std::vector<Genome*> initialPopulation,
		std::vector<float> & populationFitnesses,
		std::vector<ObjectiveFunction*> objectives,
		std::string speciesNode
	);
};
