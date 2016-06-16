#include <vector>
#pragma once

class AggregationFunction {
	private:

	protected:

	public:
	virtual ~AggregationFunction();

	virtual int aggregateFitnesses(std::vector<int> fitnesses)=0;
};
