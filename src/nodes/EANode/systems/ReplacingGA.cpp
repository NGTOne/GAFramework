#include "nodes/EANode/systems/ReplacingGA.hpp"

using namespace std;

ReplacingGA::ReplacingGA(
	SelectionStrategy * strategy
) : EvolutionarySystem(strategy) {}

ReplacingGA::ReplacingGA(
	SelectionStrategy * strategy,
	unsigned int seed
) : EvolutionarySystem(strategy, seed) {}

bool ReplacingGA::inPopulation(Genome * target, vector<Genome*> population) {
	for (unsigned int i = 0; i < population.size(); i++)
		if (population[i] == target) return true;

	return false;
}

void ReplacingGA::removeUnusedIndividuals(
	vector<Genome*> initialPopulation,
	vector<Genome*> newPopulation
) {
	for (unsigned int i = 0; i < initialPopulation.size(); i++) {
		if (!this->inPopulation(
			initialPopulation[i],
			newPopulation
		)) delete(initialPopulation[i]);
	}
}

vector<Genome*> ReplacingGA::breedMutateSelect(
	vector<Genome*> initialPopulation,
	vector<float> & populationFitnesses,
	CrossoverOperation * cross,
	MutationOperation * mutation,
	vector<ObjectiveFunction*> objectives,
	std::string speciesNode
) {
	vector<Genome*> newPopulation, children, parents;
	vector<unsigned int> parentIndices(2, 0);
	vector<float> newFitnesses(populationFitnesses);

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

		children = this->produceChildren(
			parents,
			cross,
			mutation,
			speciesNode
		);
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
