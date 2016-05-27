#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "systems/ES.hpp"

using namespace std;

ES::ES() : EvolutionarySystem(NULL) {
	init(1, 1);
}

ES::ES(unsigned seed) : EvolutionarySystem(NULL, seed) {
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

ES::ES(double muRatio, double rhoRatio) : EvolutionarySystem(NULL) {
	init(muRatio, rhoRatio);
}

ES::ES(
	double muRatio,
	double rhoRatio,
	unsigned seed
) : EvolutionarySystem(NULL, seed) {
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

int ES::getRandomParent(int populationSize) {
	uniform_int_distribution<int> selectionDist(0, populationSize-1);
	return selectionDist(generator);
}

int ES::getParent(vector<Genome*> population, vector<int> fitnesses) {
	if (this->strategy == NULL) {
		return getRandomParent(population.size());
	} else {
		return EvolutionarySystem::getParent(
			population,
			fitnesses
		);
	}
}

Genome* ES::getCrossoverChild(
	vector<Genome*> initialPopulation,
	vector<int> populationFitnesses,
	CrossoverOperation * cross
) {
	vector<Genome*> parents, children;
	for (int i = 0; i < 2; i++) {
		parents.push_back(initialPopulation[this->getParent(
			initialPopulation,
			populationFitnesses
		)]);
	}

	children = cross->crossOver(parents);
	uniform_int_distribution<int> childIndexDist(0, children.size() - 1);
	int index = childIndexDist(this->generator);

	Genome * child = new Genome(children[index], false);
	for (int i = 0; i < children.size(); i++) delete(children[i]);
	return child;
}

vector<Genome*> ES::breedMutateSelect(
	vector<Genome*> initialPopulation,
	vector<int> & populationFitnesses,
	CrossoverOperation * cross,
	MutationOperation * mutation,
	vector<ObjectiveFunction*> objectives
) {
	int initialPopSize = initialPopulation.size();
	int numMutants = initialPopSize * rhoRatio;
	int numCrossChildren = initialPopSize * muRatio; 
	vector<Genome*> crossChildren, mutantChildren, overallPopulation;
	vector<int> finalPopulationFitnesses;

	for (int i = 0; i < numMutants; i++) {
		mutantChildren.push_back(
			mutation->mutate(initialPopulation[
				this->getRandomParent(initialPopSize)
			])
		);
	}

	for (int i = 0; i < numCrossChildren; i++) {
		crossChildren.push_back(this->getCrossoverChild(
			initialPopulation, populationFitnesses, cross
		));
	}

	for (int i = 0; i < initialPopSize; i++) {
		overallPopulation.push_back(initialPopulation[i]);
		finalPopulationFitnesses.push_back(populationFitnesses[i]);
	}

	for (int i = 0; i < numMutants; i++) {
		overallPopulation.push_back(mutantChildren[i]);
		finalPopulationFitnesses.push_back(
			this->evaluateFitness(mutantChildren[i], objectives)
		);
	}

	for (int i = 0; i < numCrossChildren; i++) {
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
	for (int i = 0; i < initialPopSize; i++) {
		finalPopulation.push_back(
			new Genome(overallPopulation[i], false)
		);
		populationFitnesses[i] = finalPopulationFitnesses[i];
	}

	// A little housekeeping
	for (int i = 0; i < mutantChildren.size(); i++)
		delete(mutantChildren[i]);
	for (int i = 0; i < crossChildren.size(); i++)
		delete(crossChildren[i]);

	return finalPopulation;
}
