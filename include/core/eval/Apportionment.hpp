#ifndef CORE_EVAL_Apportionment
#define CORE_EVAL_Apportionment

#include "ObjectiveFunction.hpp"
#include "ApportionmentFunction.hpp"
#include "AggregationFunction.hpp"
#include "../PopulationNode.hpp"

class Apportionment : public ObjectiveFunction {
	private:

	protected:
	ApportionmentFunction * apportionment;
	AggregationFunction * aggregator;
	PopulationNode * upperNode;
	unsigned int tryOns;

	void init(
		PopulationNode * upperNode,
		ApportionmentFunction * apportionment,
		AggregationFunction * aggregator,
		unsigned int tryOns
	);

	float aggregateFitnesses(std::vector<float> apportionedFitnesses);
	virtual Genome * getOperableGenome(Genome * genome);
	virtual std::vector<unsigned int> getComponentIndices(
		Genome * upper,
		Genome * target
	);
	virtual std::vector<unsigned int> getRelevantIndices(
		Genome * target,
		unsigned int targetIndex
	);
	virtual bool upperGenomeUsesComponent(
		Genome * upper,
		Genome * target
	);

	void evaluatePair(
		Genome * upper,
		Genome * target,
		float upperFitness,
		std::vector<float> & apportionedFitnesses
	);

	public:
	Apportionment(
		PopulationNode * upperNode,
		ApportionmentFunction * apportionment,
		AggregationFunction * aggregator
	);
	Apportionment(
		PopulationNode * upperNode,
		ApportionmentFunction * apportionment,
		AggregationFunction * aggregator,
		unsigned int tryOns
	);

	virtual ~Apportionment();
	virtual void registerInternalObjects();

	float checkFitness(Genome * genome);

	bool isApportioning();
	ApportionmentFunction * getApportionmentFunction();
	AggregationFunction * getAggregationFunction();
};

#endif
