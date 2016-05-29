#include "../../core/PopulationNode.hpp"
#include "EvolutionarySystem.hpp"
#include "CrossoverOperation.hpp"
#include "MutationOperation.hpp"
#include <string>
#pragma once

#define EA_TYPE "evolutionary"

class EANode : public PopulationNode {
	private:

	protected:
	EvolutionarySystem * system;
	CrossoverOperation * cross;
	MutationOperation * mutation;

	void init(
		EvolutionarySystem * system,
		CrossoverOperation * cross,
		MutationOperation * mutation
	);

	public:
	EANode(
		int populationSize,
		std::vector<Locus*> loci,
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
		std::vector<Locus*> loci,
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

	virtual std::vector<Genome*> getNextPopulation();
	std::string toString();
	node_type_t type();

	EvolutionarySystem * getSystem();
	CrossoverOperation * getCrossover();
	MutationOperation * getMutation();
};
