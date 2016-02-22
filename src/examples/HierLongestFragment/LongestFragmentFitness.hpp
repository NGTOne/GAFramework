#include <libHierGA/HierGA.hpp>
#include <string>
#pragma once

class LongestFragmentFitness : public FitnessFunction {
	private:

	protected:

	public:
	LongestFragmentFitness();
	PropertiesList * checkFitness(GeneNode ** pools, int * indexes, int genomeLength);
};

class LongestFragmentToString : public ToStringFunction {
	private:

	protected:

	public:
	std::string toString(GeneNode ** pools, int * indexes, int genomeLength);
};
