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

std::vector<double> AggregatingApportionment::postProcessFitnesses(
	std::vector<double> apportionedFitnesses
) {
	return {this->aggregateFitnesses(apportionedFitnesses)};
}

double AggregatingApportionment::aggregateFitnesses(
	std::vector<double> apportionedFitnesses
) {
	return this->aggregator->aggregateFitnesses(apportionedFitnesses);
}

AggregationFunction* AggregatingApportionment::getAggregationFunction() {
	return this->aggregator;
}
