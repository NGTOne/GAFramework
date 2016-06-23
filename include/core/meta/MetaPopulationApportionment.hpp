#include "../Apportionment.hpp"
#include "../PopulationNode.hpp"
#pragma once

class MetaPopulationApportionment : public Apportionment {
	private:

	protected:
	Genome * getOperableGenome(Genome * genome);
	std::vector<unsigned int> getComponentIndices(
		Genome * upper,
		Genome * target
	);

	public:
	MetaPopulationApportionment(
		PopulationNode * metaNode,
		ApportionmentFunction * apportionment,
		AggregationFunction * aggregation
	);
};
