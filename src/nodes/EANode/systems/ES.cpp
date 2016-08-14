#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "nodes/EANode/systems/ES.hpp"
#include "nodes/EANode/selections/RandomSelection.hpp"
#include "core/utils/HierRNG.hpp"

ES::ES(
	CrossoverOperation* cross,
	MutationOperation* mutation
) : EvolutionarySystem(new RandomSelection(), cross, mutation) {
	this->init(1, 1);
}

ES::ES(
	SelectionStrategy* strategy,
	CrossoverOperation* cross,
	MutationOperation* mutation
) : EvolutionarySystem(strategy, cross, mutation) {
	this->init(1, 1);
}

ES::ES(
	double muRatio,
	double rhoRatio,
	CrossoverOperation* cross,
	MutationOperation* mutation
) : EvolutionarySystem(new RandomSelection(), cross, mutation) {
	this->init(muRatio, rhoRatio);
}

ES::ES(
	double muRatio,
	double rhoRatio,
	SelectionStrategy* strategy,
	CrossoverOperation* cross,
	MutationOperation* mutation
) : EvolutionarySystem(strategy, cross, mutation) {
	this->init(muRatio, rhoRatio);
}

void ES::init(double muRatio, double rhoRatio) {
	this->muRatio = muRatio;
	this->rhoRatio = rhoRatio;
}

Genome* ES::getCrossoverChild(
	std::vector<Genome*> initialPopulation,
	std::vector<float> populationFitnesses,
	std::string speciesNode
) {
	std::vector<Genome*> parents, children;
	for (int i = 0; i < 2; i++)
		parents.push_back(initialPopulation[this->getParent(
			initialPopulation,
			populationFitnesses
		)]);

	children = this->cross->crossOver(parents, speciesNode);
	unsigned int index = HierRNG::index(children.size() - 1);

	Genome* child = new Genome(children[index]);
	for (unsigned int i = 0; i < children.size(); i++) delete(children[i]);
	return child;
}

std::vector<Genome*> ES::breedMutateSelect(
	std::vector<Genome*> initialPopulation,
	std::vector<float>& populationFitnesses,
	std::vector<ObjectiveFunction*> objectives,
	std::string speciesNode
) {
	unsigned int initialPopSize = initialPopulation.size();
	unsigned int numMutants = initialPopSize * rhoRatio;
	unsigned int numCrossChildren = initialPopSize * muRatio;
	std::vector<Genome*> crossChildren, mutantChildren, overallPopulation;
	std::vector<float> finalPopulationFitnesses;

	for (unsigned int i = 0; i < numMutants; i++)
		mutantChildren.push_back(
			this->mutation->mutate(initialPopulation[
				this->getParent(
					initialPopulation,
					populationFitnesses
				)
			])
		);

	for (unsigned int i = 0; i < numCrossChildren; i++)
		crossChildren.push_back(this->getCrossoverChild(
			initialPopulation,
			populationFitnesses,
			speciesNode
		));

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

	std::vector<Genome*> finalPopulation;

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
