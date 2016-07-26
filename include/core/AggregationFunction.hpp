#include <vector>
#include "EABehaviourObject.hpp"
#pragma once

class AggregationFunction : public EABehaviourObject {
	private:

	protected:

	public:
	virtual ~AggregationFunction();
	virtual void registerInternalObjects(NodeGarbageCollector & collector);

	virtual float aggregateFitnesses(std::vector<float> fitnesses)=0;
};
