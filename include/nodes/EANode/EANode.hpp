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

	void init(
		EvolutionarySystem * system
	);

	public:
	EANode(
		unsigned int populationSize,
		std::vector<Locus*> loci,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition *> conditions,
		std::string name,
		EvolutionarySystem * system
	);

	EANode(
		unsigned int populationSize,
		std::vector<Locus*> loci,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition *> conditions,
		std::string name,
		unsigned int accelerationFactor,
		EvolutionarySystem * system
	);

	virtual std::vector<Genome*> getNextPopulation();
	std::string toString();
	node_type_t type();

	EvolutionarySystem * getSystem();

	PopulationNode * duplicate(std::string newNodeName);
};
