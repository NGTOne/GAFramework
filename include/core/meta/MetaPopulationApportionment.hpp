#include "../eval/Apportionment.hpp"
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
	std::vector<unsigned int> getRelevantIndices(
		Genome * target,
		unsigned int targetIndex
	);
	bool upperGenomeUsesComponent(Genome * upper, Genome * target);

	public:
	MetaPopulationApportionment(
		PopulationNode * metaNode,
		ApportionmentFunction * apportionment,
		AggregationFunction * aggregation
	);
};
