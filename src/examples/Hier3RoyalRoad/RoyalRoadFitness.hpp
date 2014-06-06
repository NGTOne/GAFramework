#include <libGAFramework/GAFramework.hpp>
#include <string>
#pragma once

class RoyalRoadFitness : public FitnessFunction {
	private:

	protected:

	public:
	RoyalRoadFitness();
	PropertiesList * checkFitness(GenePool ** pools, int * indexes, int genomeLength);

	std::string toString(GenePool ** pools, int * indexes, int genomeLength);
};
