#include <libHierGA/HierGA.hpp>
#include <string>
#pragma once

class OneMaxFitness : public FitnessFunction {
	private:

	protected:

	public:
	OneMaxFitness();
	PropertiesList * checkFitness(GenePool ** pools, int * indexes, int genomeLength);
};

class OneMaxToString : public ToStringFunction {
	private:

	protected:

	public:
	std::string toString(GenePool ** pools, int * indexes, int genomeLength);
};
