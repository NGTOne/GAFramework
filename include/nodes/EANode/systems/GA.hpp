#ifndef NODES_EANODE_SYSTEMS_GA
#define NODES_EANODE_SYSTEMS_GA

#include "../EvolutionarySystem.hpp"
#include <string>
#include <vector>

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
		std::vector<float> initialPopulationFitnesses,
		std::vector<Genome*> & newPopulation,
		std::vector<float> & newPopulationFitnesses
	);
	std::vector<unsigned int> findElites(std::vector<float> fitnesses);

	public:

	GA(
		unsigned int numElites,
		bool randomElitePlacement,
		SelectionStrategy * strategy,
		CrossoverOperation * cross,
		MutationOperation * mutation
	);
	GA(
		unsigned int numElites,
		SelectionStrategy * strategy,
		CrossoverOperation * cross,
		MutationOperation * mutation
	);

	std::vector<Genome*> breedMutateSelect(
		std::vector<Genome*> initialPopulation,
		std::vector<float> & populationFitnesses,
		std::vector<ObjectiveFunction*> objectives,
		std::string speciesNode
	);
};

#endif
