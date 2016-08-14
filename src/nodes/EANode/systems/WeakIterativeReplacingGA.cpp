#include <random>
#include "nodes/EANode/systems/WeakIterativeReplacingGA.hpp"
#include "core/utils/HierRNG.hpp"

WeakIterativeReplacingGA::WeakIterativeReplacingGA(
	SelectionStrategy* strategy,
	CrossoverOperation* cross,
	MutationOperation* mutation
) : ReplacingGA(strategy, cross, mutation) {}

std::vector<Genome*> WeakIterativeReplacingGA::breedMutateSelect(
	std::vector<Genome*> initialPopulation,
	std::vector<float>& populationFitnesses,
	std::vector<ObjectiveFunction*> objectives,
	std::string speciesNode
) {
	std::vector<std::vector<Genome*>> possibleContenders(
		initialPopulation.size(),
		std::vector<Genome*>()
	);
	std::vector<Genome*> newPopulation(initialPopulation.size(), NULL);
	std::vector<float> newFitnesses(initialPopulation.size(), 0);

	for (unsigned int i = 0; i < initialPopulation.size(); i++) {
		std::vector<unsigned int> parentIndices;
		std::vector<Genome*> parents, children;
		parentIndices.push_back(i);
		parentIndices.push_back(this->getParent(
			initialPopulation,
			populationFitnesses
		));

		for (unsigned int k = 0; k < parentIndices.size(); k++)
			parents.push_back(initialPopulation[parentIndices[k]]);

		children = this->produceChildren(parents, speciesNode);

		for (unsigned int k = 0; k < children.size(); k++)
			possibleContenders[parentIndices[k]].push_back(
				children[k]
			);
	}

	for (unsigned int i = 0; i < initialPopulation.size(); i++) {
		unsigned int index = HierRNG::index(
			possibleContenders[i].size() - 1
		);
		Genome* child = possibleContenders[i][index];
		float childFitness = this->evaluateFitness(child, objectives);

		if (childFitness > populationFitnesses[i]) {
			newPopulation[i] = new Genome(child);
			newFitnesses[i] = childFitness;
		} else {
			newPopulation[i] = new Genome(initialPopulation[i]);
			newFitnesses[i] = populationFitnesses[i];
		}

		for (unsigned int k = 0; k < possibleContenders[i].size(); k++)
			delete(possibleContenders[i][k]);
	}

	populationFitnesses = newFitnesses;
	return(newPopulation);
}
