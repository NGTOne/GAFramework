#include <libHierGA/HierGA.hpp>
#include <string>
#pragma once

class HierRoyalRoadFitness : public FitnessFunction {
	private:

	protected:

	public:
	HierRoyalRoadFitness();
	PropertiesList * checkFitness(GeneNode ** pools, int * indexes, int genomeLength);
};

class HierRoyalRoadToString : public ToStringFunction {
	private:

	protected:

	public:
	std::string toString(GeneNode ** pools, int * indexes, int genomeLength);
};
