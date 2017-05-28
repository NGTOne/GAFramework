#ifndef CORE_EVAL_Apportionment
#define CORE_EVAL_Apportionment

#include "ObjectiveFunction.hpp"
#include "ApportionmentFunction.hpp"
#include "../PopulationNode.hpp"

class Apportionment : public ObjectiveFunction {
	private:

	protected:
	ApportionmentFunction * apportionment;
	PopulationNode * upperNode;
	unsigned int tryOns;

	void init(
		PopulationNode * upperNode,
		ApportionmentFunction * apportionment,
		unsigned int tryOns
	);

	virtual std::vector<FitnessPair> postProcessFitnesses(
		std::vector<FitnessPair> apportionedFitnesses
	);

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
		Genome* upper,
		Genome* rawUpper,
		Genome* target,
		Fitness upperFitness,
		std::vector<FitnessPair>& apportionedFitnesses
	);

	public:
	Apportionment(
		PopulationNode * upperNode,
		ApportionmentFunction * apportionment
	);
	Apportionment(
		PopulationNode * upperNode,
		ApportionmentFunction * apportionment,
		unsigned int tryOns
	);

	virtual ~Apportionment();
	virtual void registerInternalObjects();

	Fitness checkFitness(Genome* genome);

	bool isApportioning();
	ApportionmentFunction * getApportionmentFunction();
};

#endif
