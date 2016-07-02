#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "systems/ES.hpp"
#include "selections/RandomSelection.hpp"

using namespace std;

ES::ES() : EvolutionarySystem(new RandomSelection()) {
	init(1, 1);
}

ES::ES(unsigned seed) : EvolutionarySystem(new RandomSelection(), seed) {
	init(1, 1);
}

ES::ES(SelectionStrategy * strategy) : EvolutionarySystem(strategy) {
	init(1, 1);
}

ES::ES(
	SelectionStrategy * strategy,
	unsigned seed
) : EvolutionarySystem(strategy, seed) {
	init(1, 1);
}

ES::ES(
	double muRatio,
	double rhoRatio
) : EvolutionarySystem(
	new RandomSelection()
) {
	init(muRatio, rhoRatio);
}

ES::ES(
	double muRatio,
	double rhoRatio,
	unsigned seed
) : EvolutionarySystem(new RandomSelection(), seed) {
	init(muRatio, rhoRatio);
}

ES::ES(
	double muRatio,
	double rhoRatio,
	SelectionStrategy * strategy
) : EvolutionarySystem(strategy) {
	init(muRatio, rhoRatio);
}

ES::ES(
	double muRatio,
	double rhoRatio,
	SelectionStrategy * strategy,
	unsigned seed
) : EvolutionarySystem(strategy, seed) {
	init(muRatio, rhoRatio);
}

void ES::init(double muRatio, double rhoRatio) {
	this->muRatio = muRatio;
	this->rhoRatio = rhoRatio;
}

Genome* ES::getCrossoverChild(
	vector<Genome*> initialPopulation,
	vector<float> populationFitnesses,
	CrossoverOperation * cross,
	std::string speciesNode
) {
	vector<Genome*> parents, children;
	for (int i = 0; i < 2; i++) {
		parents.push_back(initialPopulation[this->getParent(
			initialPopulation,
			populationFitnesses
		)]);
	}

	children = cross->crossOver(parents, speciesNode);
	uniform_int_distribution<unsigned int> childIndexDist(
		0,
		children.size() - 1
	);
	unsigned int index = childIndexDist(this->generator);

	Genome * child = new Genome(children[index]);
	for (unsigned int i = 0; i < children.size(); i++) delete(children[i]);
	return child;
}

vector<Genome*> ES::breedMutateSelect(
	vector<Genome*> initialPopulation,
	vector<float> & populationFitnesses,
	CrossoverOperation * cross,
	MutationOperation * mutation,
	vector<ObjectiveFunction*> objectives,
	std::string speciesNode
) {
	unsigned int initialPopSize = initialPopulation.size();
	unsigned int numMutants = initialPopSize * rhoRatio;
	unsigned int numCrossChildren = initialPopSize * muRatio;
	vector<Genome*> crossChildren, mutantChildren, overallPopulation;
	vector<float> finalPopulationFitnesses;

	for (unsigned int i = 0; i < numMutants; i++) {
		mutantChildren.push_back(
			mutation->mutate(initialPopulation[
				this->getParent(
					initialPopulation,
					populationFitnesses
				)
			])
		);
	}

	for (unsigned int i = 0; i < numCrossChildren; i++) {
		crossChildren.push_back(this->getCrossoverChild(
			initialPopulation,
			populationFitnesses,
			cross,
			speciesNode
		));
	}

	for (unsigned int i = 0; i < initialPopSize; i++) {
		overallPopulation.push_back(initialPopulation[i]);
		finalPopulationFitnesses.push_back(populationFitnesses[i]);
	}

	for (unsigned int i = 0; i < numMutants; i++) {
		overallPopulation.push_back(mutantChildren[i]);
		finalPopulationFitnesses.push_back(
			this->evaluateFitness(mutantChildren[i], objectives)
		);
	}

	for (unsigned int i = 0; i < numCrossChildren; i++) {
		overallPopulation.push_back(crossChildren[i]);
		finalPopulationFitnesses.push_back(
			this->evaluateFitness(crossChildren[i], objectives)
		);
	}

	this->sortPopulation(
		overallPopulation,
		finalPopulationFitnesses
	);

	vector<Genome*> finalPopulation;

	//Since they're sorted, the best of the new generation can simply be
	//pulled from the top of the list
	for (unsigned int i = 0; i < initialPopSize; i++) {
		finalPopulation.push_back(
			new Genome(overallPopulation[i])
		);
		populationFitnesses[i] = finalPopulationFitnesses[i];
	}

	// A little housekeeping
	for (unsigned int i = 0; i < mutantChildren.size(); i++)
		delete(mutantChildren[i]);
	for (unsigned int i = 0; i < crossChildren.size(); i++)
		delete(crossChildren[i]);

	return finalPopulation;
}
