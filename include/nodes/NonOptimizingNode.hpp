#include "core/PopulationNode.hpp"
#pragma once

class NonOptimizingNode : public PopulationNode {
	private:

	protected:

	public:
	NonOptimizingNode(
		int populationSize,
		std::vector<Locus*> loci,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition *> conditions,
		std::string name
	);

	void nextIteration();
};
