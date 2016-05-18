#include "../../core/Genome.hpp"
#include "SelectionStrategy.hpp"
#include "CrossoverOperation.hpp"
#include "../../core/ObjectiveFunction.hpp"
#include "MutationOperation.hpp"
#include <random>
#include <string>
#include <vector>
#pragma once

class EvolutionarySystem {
	private:

	protected:
	unsigned seed;
	std::mt19937 generator;
	SelectionStrategy * strategy;

	void init(SelectionStrategy * strategy, unsigned seed);
	void sortPopulation(
		std::vector<Genome*> &population,
		std::vector<int> &fitnesses
	);
	int evaluateFitness(
		Genome * target,
		std::vector<ObjectiveFunction*> objectives
	);

	public:
	EvolutionarySystem(SelectionStrategy * strategy);
	EvolutionarySystem(SelectionStrategy * strategy, unsigned seed);

	virtual int getParent(
		std::vector<Genome*> population,
		std::vector<int> fitnesses
	);
	virtual std::vector<Genome*> breedMutateSelect(
		std::vector<Genome*> initialPopulation,
		std::vector<int> & populationFitnesses,
		CrossoverOperation * cross,
		MutationOperation * mutation,
		std::vector<ObjectiveFunction*> objectives
	)=0;

	std::string toString();
};
