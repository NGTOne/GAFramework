#include "../nodes/EANode/EvolutionarySystem.hpp"
#include <random>
#include <string>
#include <vector>
#pragma once

/*
* The ES model uses the (mu/rho+, lambda)-ES model, which is an
* extension of the original ES model proposed by Ingo Rechenberg et. al. in
* the 1960s.
*
* In this model, the original population, the offspring created by crossover,
* and the offspring created by mutation (which is done independently of
* crossover) are all combined into one population and sorted, with the next
* generation being the members of the combined population that are the
* most fit.
*/

class ES : public EvolutionarySystem {
	private:

	protected:
	double muRatio;
	double rhoRatio;

	void init(double muRatio, double rhoRatio);

	Genome * getCrossoverChild(
		vector<Genome*> initialPopulation,
		vector<int> populationFitnesses,
		CrossoverOperation * cross,
		std::string speciesNode
	);

	public:
	ES();
	ES(SelectionStrategy * strategy);
	ES(unsigned seed);
	ES(SelectionStrategy * strategy, unsigned seed);
	ES(double muRatio, double rhoRatio);
	ES(double muRatio, double rhoRatio, unsigned seed);
	ES(double muRatio, double rhoRatio, SelectionStrategy * strategy);
	ES(
		double muRatio,
		double rhoRatio,
		SelectionStrategy * strategy,
		unsigned seed
	);

	std::vector<Genome*> breedMutateSelect(
		std::vector<Genome*> initialPopulation,
		std::vector<int> & populationFitnesses,
		CrossoverOperation * cross,
		MutationOperation * mutation,
		std::vector<ObjectiveFunction*> objectives,
		std::string speciesNode
	);
};
