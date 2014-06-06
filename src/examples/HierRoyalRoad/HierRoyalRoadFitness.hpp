#include <libGAFramework/GAFramework.hpp>
#include <string>
#pragma once

class HierRoyalRoadFitness : public FitnessFunction {
	private:

	protected:

	public:
	HierRoyalRoadFitness();
	PropertiesList * checkFitness(GenePool ** pools, int * indexes, int genomeLength);

	std::string toString(GenePool ** pools, int * indexes, int genomeLength);
};
