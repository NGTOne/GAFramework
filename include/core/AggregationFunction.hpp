#include <vector>
#pragma once

class AggregationFunction {
	private:

	protected:

	public:
	virtual int aggregateFitnesses(std::vector<int> fitnesses)=0;
};
