#include "nodes/EANode/systems/ES.hpp"
#include "nodes/EANode/selections/RandomSelection.hpp"

ES::ES(
	MutationOperation* mutation
) : EvolutionarySystem(new RandomSelection(), NULL, mutation) {}

ES::ES(
	CrossoverOperation* cross,
	MutationOperation* mutation
) : EvolutionarySystem(new RandomSelection(), cross, mutation) {}

ES::ES(
	SelectionStrategy* strategy,
	CrossoverOperation* cross,
	MutationOperation* mutation
) : EvolutionarySystem(strategy, cross, mutation) {}

std::vector<Genome*> ES::breedMutateSelect(
	std::vector<Genome*> initialPopulation,
	std::vector<float>& populationFitnesses,
	std::vector<ObjectiveFunction*> objectives,
	std::string speciesNode
) {
	std::vector<Genome*> offspring = this->getOffspring(
		initialPopulation,
		populationFitnesses,
		speciesNode
	);
	std::vector<Genome*> results = this->doReplacement(
		offspring,
		initialPopulation,
		populationFitnesses,
		objectives
	);
	std::vector<Genome*> finalResults;
	for (auto genome: results) finalResults.push_back(new Genome(genome));
	for (auto off: offspring) delete(off);
	return finalResults;
}
