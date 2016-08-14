#include "../../core/Genome.hpp"
#include "SelectionStrategy.hpp"
#include "CrossoverOperation.hpp"
#include "../../core/eval/ObjectiveFunction.hpp"
#include "../../core/EABehaviourObject.hpp"
#include "MutationOperation.hpp"
#include <random>
#include <string>
#include <vector>
#pragma once

class EvolutionarySystem : public EABehaviourObject {
	private:

	protected:
	SelectionStrategy * strategy;
	CrossoverOperation * cross;
	MutationOperation * mutation;

	void init(
		SelectionStrategy * strategy,
		CrossoverOperation * cross,
		MutationOperation * mutation
	);
	void sortPopulation(
		std::vector<Genome*> & population,
		std::vector<float> & fitnesses
	);
	float evaluateFitness(
		Genome * target,
		std::vector<ObjectiveFunction*> objectives
	);

	virtual unsigned int getParent(
		std::vector<Genome*> population,
		std::vector<float> fitnesses
	);

	std::vector<Genome*> produceChildren(
		std::vector<Genome*> parents,
		std::string speciesNode
	);

	public:
	EvolutionarySystem(
		SelectionStrategy * strategy,
		CrossoverOperation * cross,
		MutationOperation * mutation
	);
	virtual ~EvolutionarySystem();
	virtual void registerInternalObjects();

	virtual std::vector<Genome*> breedMutateSelect(
		std::vector<Genome*> initialPopulation,
		std::vector<float> & populationFitnesses,
		std::vector<ObjectiveFunction*> objectives,
		std::string speciesNode
	)=0;

	std::string toString();
	SelectionStrategy * getSelectionStrategy();
	CrossoverOperation * getCrossover();
	MutationOperation * getMutation();
	virtual bool hasNiching();
};
