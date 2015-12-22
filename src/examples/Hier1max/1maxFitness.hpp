#include <libHierGA/HierGA.hpp>
#include <string>
#pragma once

class OneMaxFitness : public FitnessFunction {
	private:

	protected:

	public:
	OneMaxFitness();
	PropertiesList * checkFitness(GeneNode ** pools, int * indexes, int genomeLength);
};

class OneMaxToString : public ToStringFunction {
	private:

	protected:

	public:
	std::string toString(GeneNode ** pools, int * indexes, int genomeLength);
};
