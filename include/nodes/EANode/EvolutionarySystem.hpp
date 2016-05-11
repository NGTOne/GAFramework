#include "../../core/Genome.hpp"
#include "SelectionStrategy.hpp"
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

	public:
	EvolutionarySystem(SelectionStrategy * strategy);
	EvolutionarySystem(SelectionStrategy * strategy, unsigned seed);

	virtual int getParent(
		std::vector<Genome*> population,
		std::vector<int> fitnesses
	);
	virtual std::vector<Genome*> breedMutateSelect(
		std::vector<Genome*> population,
		std::vector<int> fitnesses
	)=0;

	std::string toString();
};
