#include "../../core/PopulationNode.hpp"
#include "EvolutionarySystem.hpp"
#include "CrossoverOperation.hpp"
#include "MutationOperation.hpp"
#include <string>
#pragma once

class EANode : public PopulationNode {
	private:

	protected:
	EvolutionarySystem * system;
	CrossoverOperation * cross;
	MutationOperation * mutation;

	public:
	EANode(
		int populationSize,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition *> conditions,
		std::string name,
		EvolutionarySystem * system,
		CrossoverOperation * cross,
		MutationOperation * mutation
	);

	EANode(
		int populationSize,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition *> conditions,
		std::string name,
		int accelerationFactor,
		EvolutionarySystem * system,
		CrossoverOperation * cross,
		MutationOperation * mutation
	);

	~EANode();

	void init(
		EvolutionarySystem * system,
		CrossoverOperation * cross,
		MutationOperation * mutation
	);

	virtual void nextIteration();
};
