#include <libHierGA/HierGA.hpp>
#include <string>
#pragma once

class RoyalRoadFitness : public FitnessFunction {
	private:

	protected:

	public:
	RoyalRoadFitness();
	PropertiesList * checkFitness(GeneNode ** pools, int * indexes, int genomeLength);
};

class RoyalRoadToString : public ToStringFunction {
	private:

	protected:

	public:
	std::string toString(GeneNode ** pools, int * indexes, int genomeLength);
};
