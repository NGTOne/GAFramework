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
	Genome * getOperableGenome(Genome * genome);

	public:
	MetaPopulationApportionment(
		PopulationNode * metaNode,
		ApportionmentFunction * apportionment,
		AggregationFunction * aggregation
	);
};
