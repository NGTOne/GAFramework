#include "PopulationNode.hpp"
#pragma once

class NonEvolvingPopulationNode : public PopulationNode {
	private:

	protected:

	public:
	NonEvolvingPopulationNode(
		int populationSize,
		std::vector<ObjectiveFunction*> objectives,
		ToStringFunction * populationToString,
		std::vector<EndCondition *> conditions,
		std::string name
	);

	void nextIteration();
	std::string toString();
};
