#ifndef CORE_EVAL_AggregationFunction
#define CORE_EVAL_AggregationFunction

#include <vector>
#include "../EABehaviourObject.hpp"

class AggregationFunction : public EABehaviourObject {
	private:

	protected:

	public:
	virtual ~AggregationFunction();

	virtual double aggregateFitnesses(std::vector<double> fitnesses)=0;
};

#endif
