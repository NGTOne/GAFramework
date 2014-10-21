#include <libHierGA/HierGA.hpp>
#include <string>
#pragma once

class HierRoyalRoadFitness : public FitnessFunction {
	private:

	protected:

	public:
	HierRoyalRoadFitness();
	PropertiesList * checkFitness(GenePool ** pools, int * indexes, int genomeLength);
};

class HierRoyalRoadToString : public ToStringFunction {
	private:

	protected:

	public:
	std::string toString(GenePool ** pools, int * indexes, int genomeLength);
};
