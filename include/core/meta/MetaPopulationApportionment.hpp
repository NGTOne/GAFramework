#include "../Apportionment.hpp"
#include "../ObjectiveFunction.hpp"
#pragma once

class MetaPopulationApportionment : public Apportionment {
	private:

	protected:
	Apportionment * flattenedApportionment;

	int aggregateFitnesses(std::vector<int> apportionedFitnesses);

	public:
	MetaPopulationApportionment(
		PopulationNode * metaNode,
		Apportionment * flattenedApportionment
	);
};
