#ifndef NODES_EANODE_SYSTEMS_ES
#define NODES_EANODE_SYSTEMS_ES

#include "../EvolutionarySystem.hpp"
#include <string>
#include <vector>

class ES : public EvolutionarySystem {
	private:

	protected:
	ES(MutationOperation* mutation);
	ES(CrossoverOperation* cross, MutationOperation* mutation);
	ES(
		SelectionStrategy* strategy,
		CrossoverOperation* cross,
		MutationOperation* mutation
	);

	virtual std::vector<Genome*> getOffspring(
		std::vector<Genome*> parents,
		std::vector<Fitness> parentFitnesses,
		std::string speciesNode
	)=0;
	virtual std::vector<Genome*> doReplacement(
		std::vector<Genome*> parents,
		std::vector<Genome*> offspring,
		std::vector<Fitness>& populationFitnesses,
		std::vector<ObjectiveFunction*> objectives
	)=0;

	public:
	virtual std::vector<Genome*> breedMutateSelect(
		std::vector<Genome*> initialPopulation,
		std::vector<Fitness>& populationFitnesses,
		std::vector<ObjectiveFunction*> objectives,
		std::string speciesNode
	);
};

#endif
