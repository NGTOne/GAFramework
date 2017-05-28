#include "core/eval/AggregatingApportionment.hpp"
#include "core/utils/HierGC.hpp"

AggregatingApportionment::AggregatingApportionment(
	PopulationNode* upperNode,
	ApportionmentFunction* apportionment,
	AggregationFunction* aggregator
): Apportionment(upperNode, apportionment) {
	this->aggregator = aggregator;
}

AggregatingApportionment::AggregatingApportionment(
	PopulationNode * upperNode,
	ApportionmentFunction * apportionment,
	AggregationFunction* aggregator,
	unsigned int tryOns
): Apportionment(upperNode, apportionment, tryOns) {
	this->aggregator = aggregator;
}

void AggregatingApportionment::registerInternalObjects() {
	Apportionment::registerInternalObjects();
	HierGC::registerObject(this->aggregator);
}

std::vector<FitnessPair> AggregatingApportionment::postProcessFitnesses(
	std::vector<FitnessPair> apportionedFitnesses
) {
	return {std::make_tuple(
		this->aggregateFitnesses(apportionedFitnesses),
		FitnessSource(this)
	)};
}

double AggregatingApportionment::aggregateFitnesses(
	std::vector<FitnessPair> apportionedFitnesses
) {
	std::vector<double> fitnessValues;
	for (auto pair: apportionedFitnesses)
		fitnessValues.push_back(std::get<0>(pair));
	return this->aggregator->aggregateFitnesses(fitnessValues);
}

AggregationFunction* AggregatingApportionment::getAggregationFunction() {
	return this->aggregator;
}
