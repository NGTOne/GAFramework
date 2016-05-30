#include "../nodes/EANode/EvolutionarySystem.hpp"
#include <string>
#include <vector>
#pragma once

/*
* The GA model reflects the "classic" GA, as popularized by the work
* of John Holland in the 1970s.
*
* In this model, a few elites (the best of the previous generation) are
* selected and allowed to survive to the next generation. The remainder of
* the next generation is filled in with new offspring that are created by a
* combination of crossover and mutation.
*/

class GA : public EvolutionarySystem {
	private:

	protected:
	unsigned int numElites;
	bool randomElitePlacement;

	void init(unsigned int numElites, bool randomElitePlacement);
	void placeElites(
		std::vector<Genome*> initialPopulation,
		std::vector<int> initialPopulationFitnesses,
		std::vector<Genome*> & newPopulation,
		std::vector<int> & newPopulationFitnesses
	);
	std::vector<unsigned int> findElites(std::vector<int> fitnesses);

	public:

	GA(
		unsigned int numElites,
		bool randomElitePlacement,
		SelectionStrategy * strategy
	);

	GA(
		unsigned int numElites,
		SelectionStrategy * strategy
	);

	GA(
		unsigned int numElites,
		bool randomElitePlacement,
		SelectionStrategy * strategy,
		unsigned seed
	);

	std::vector<Genome*> breedMutateSelect(
		std::vector<Genome*> initialPopulation,
		std::vector<int> & populationFitnesses,
		CrossoverOperation * cross,
		MutationOperation * mutation,
		std::vector<ObjectiveFunction*> objectives
	);
};
