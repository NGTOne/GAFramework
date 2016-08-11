#include "nodes/EANode/systems/ReplacingGA.hpp"

ReplacingGA::ReplacingGA(
	SelectionStrategy* strategy,
	CrossoverOperation* cross,
	MutationOperation* mutation
) : EvolutionarySystem(strategy, cross, mutation) {}

bool ReplacingGA::inPopulation(
	Genome * target,
	std::vector<Genome*> population
) {
	for (unsigned int i = 0; i < population.size(); i++)
		if (population[i] == target) return true;

	return false;
}

void ReplacingGA::removeUnusedIndividuals(
	std::vector<Genome*> initialPopulation,
	std::vector<Genome*> newPopulation
) {
	for (unsigned int i = 0; i < initialPopulation.size(); i++) {
		if (!this->inPopulation(
			initialPopulation[i],
			newPopulation
		)) delete(initialPopulation[i]);
	}
}

std::vector<Genome*> ReplacingGA::breedMutateSelect(
	std::vector<Genome*> initialPopulation,
	std::vector<float>& populationFitnesses,
	std::vector<ObjectiveFunction*> objectives,
	std::string speciesNode
) {
	std::vector<Genome*> newPopulation, children, parents;
	std::vector<unsigned int> parentIndices(2, 0);
	std::vector<float> newFitnesses(populationFitnesses);

	for (unsigned int i = 0; i < initialPopulation.size(); i++)
		newPopulation.push_back(new Genome(initialPopulation[i]));

	for (unsigned int i = 0; i < initialPopulation.size()/2; i++) {
		for (int k = 0; k < 2; k++) {
			parentIndices[k] = this->getParent(
				initialPopulation,
				populationFitnesses
			);
			parents.push_back(initialPopulation[parentIndices[k]]);
		}

		children = this->produceChildren(parents, speciesNode);
		parents.clear();

		for (unsigned int k = 0; k < children.size(); k++) {
			float childFitness = this->evaluateFitness(
				children[k],
				objectives
			);

			if (childFitness > newFitnesses[parentIndices[k]]) {
				delete(newPopulation[parentIndices[k]]);
				newPopulation[parentIndices[k]] = children[k];
				newFitnesses[parentIndices[k]] = childFitness;
			} else {
				delete(children[k]);
			}
		}
	}

	populationFitnesses = newFitnesses;
	return(newPopulation);
}
