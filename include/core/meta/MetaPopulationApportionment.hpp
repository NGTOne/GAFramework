#ifndef CORE_META_MetaPopulationApportionment
#define CORE_META_MetaPopulationApportionment

#include "../eval/Apportionment.hpp"
#include "../PopulationNode.hpp"

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

#endif
