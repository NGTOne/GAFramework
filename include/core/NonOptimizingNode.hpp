#include "PopulationNode.hpp"
#pragma once

class NonEvolvingPopulationNode : public PopulationNode {
	private:

	protected:

	public:
	NonEvolvingPopulationNode(
		int populationSize,
		std::vector<ObjectiveFunction*> objectives,
		std::string name,
	);

	void nextIteration();
	std::string toString();
};
