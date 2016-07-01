#include <vector>
#pragma once

class AggregationFunction {
	private:

	protected:

	public:
	virtual ~AggregationFunction();

	virtual float aggregateFitnesses(std::vector<float> fitnesses)=0;
};
