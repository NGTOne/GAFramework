#include <libHierGA/HierGA.hpp>
#include <string>
#pragma once

class HierLongestFragmentFitness : public FitnessFunction {
	private:

	protected:

	public:
	HierLongestFragmentFitness();
	PropertiesList * checkFitness(GeneNode ** pools, int * indexes, int genomeLength);
};

class HierLongestFragmentToString : public ToStringFunction {
	private:

	protected:

	public:
	std::string toString(GeneNode ** pools, int * indexes, int genomeLength);
};
