#include <random>
#include "systems/WeakIterativeReplacingGA.hpp"

using namespace std;

WeakIterativeReplacingGA::WeakIterativeReplacingGA(
	SelectionStrategy * strategy
) : ReplacingGA(strategy) {}

WeakIterativeReplacingGA::WeakIterativeReplacingGA(
	SelectionStrategy * strategy,
	unsigned seed
) : ReplacingGA(strategy, seed) {}

vector<Genome*> WeakIterativeReplacingGA::breedMutateSelect(
	vector<Genome*> initialPopulation,
	vector<int> & populationFitnesses,
	CrossoverOperation * cross,
	MutationOperation * mutation,
	vector<ObjectiveFunction*> objectives
) {
	vector<vector<Genome*>> possibleContenders(
		initialPopulation.size(),
		vector<Genome*>()
	);
	vector<Genome*> newPopulation(initialPopulation.size(), NULL);
	vector<int> newFitnesses(initialPopulation.size(), 0);

	for (int i = 0; i < initialPopulation.size(); i++) {
		vector<int> parentIndices;
		vector<Genome*> parents, children;
		parentIndices.push_back(i);
		parentIndices.push_back(this->getParent(
			initialPopulation,
			populationFitnesses
		));

		for (int k = 0; k < parentIndices.size(); k++)
			parents.push_back(initialPopulation[parentIndices[k]]);

		children = this->produceChildren(parents, cross, mutation);

		for (int k = 0; k < children.size(); k++)
			possibleContenders[parentIndices[k]].push_back(
				children[k]
			);
	}

	for (int i = 0; i < initialPopulation.size(); i++) {
		uniform_int_distribution<int> childSelectionDist(
			0,
			possibleContenders[i].size() - 1
		);
		int index = childSelectionDist(generator);
		Genome * child = possibleContenders[i][index];
		int childFitness = this->evaluateFitness(child, objectives);

		if (childFitness > populationFitnesses[i]) {
			newPopulation[i] = new Genome(child);
			newFitnesses[i] = childFitness;
		} else {
			newPopulation[i] = new Genome(initialPopulation[i]);
			newFitnesses[i] = populationFitnesses[i];
		}

		for (int k = 0; k < possibleContenders[i].size(); k++)
			delete(possibleContenders[i][k]);
	}

	populationFitnesses = newFitnesses;
	return(newPopulation);
}
