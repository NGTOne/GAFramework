#include "MetaPopulationFunction.hpp"
#include "../Apportionment.hpp"
#include "../PopulationNode.hpp"
#pragma once

class MetaPopulationApportionment :
	public MetaPopulationFunction,
	public Apportionment
{
	private:

	protected:

	public:
	MetaPopulationApportionment(
		PopulationNode * metaNode,
		ApportionmentFunction * func
	);
	int checkFitness(Genome * genome);
};
