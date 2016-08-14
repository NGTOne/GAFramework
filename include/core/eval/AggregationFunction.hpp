#include <vector>
#include "../EABehaviourObject.hpp"
#pragma once

class AggregationFunction : public EABehaviourObject {
	private:

	protected:

	public:
	virtual ~AggregationFunction();

	virtual float aggregateFitnesses(std::vector<float> fitnesses)=0;
};
