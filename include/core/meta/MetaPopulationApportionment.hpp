#include "MetaPopulationFunction.hpp"
#include "../Apportionment.hpp"
#pragma once

class MetaPopulationApportionment : public MetaPopulationFunction {
	private:

	protected:
	Apportionment * flattenedApportionment;

	public:
	MetaPopulationApportionment(
		PopulationNode * metaNode,
		Apportionment * flattenedApportionment
	);
	int checkFitness(Genome * genome);

	ObjectiveFunction * getFunction();
};
