#include <libHierGA/HierGA.hpp>
#include <string>
#pragma once

class HierOneMaxFitness : public FitnessFunction {
	private:

	protected:

	public:
	HierOneMaxFitness();
	PropertiesList * checkFitness(GenePool ** pools, int * indexes, int genomeLength);
};

class HierOneMaxToString : public ToStringFunction {
	private:

	protected:

	public:
	std::string toString(GenePool ** pools, int * indexes, int genomeLength);
};
