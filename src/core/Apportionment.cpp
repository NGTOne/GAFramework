#include "core/Apportionment.hpp"

Apportionment::Apportionment(
	PopulationNode * upperNode,
	ApportionmentFunction * apportionment,
	AggregationFunction * aggregator
) {
	this->apportionment = apportionment;
	this->aggregator = aggregator;
	this->upperNode = upperNode;
}

Apportionment::~Apportionment() {}

Genome * Apportionment::getOperableGenome(Genome * genome) {
	return new Genome(genome);
}

int Apportionment::checkFitness(Genome * genome) {
	std::vector<int> apportionedFitnesses;

	for (unsigned int i = 0; i < this->upperNode->populationSize(); i++) {
		Genome * provider = this->upperNode->getIndex(i);
		if (provider->usesComponent(genome)) {
			Genome * operable = this->getOperableGenome(genome);
			apportionedFitnesses.push_back(
				this->apportionment->apportionFitness(
					operable,
					provider,
					this->upperNode->getFitnessAtIndex(i)
				)
			);
			delete(operable);
		}
	}

	return this->aggregateFitnesses(apportionedFitnesses);
}

int Apportionment::aggregateFitnesses(std::vector<int> apportionedFitnesses) {
	return this->aggregator->aggregateFitnesses(apportionedFitnesses);
}

bool Apportionment::isApportioning() {
	return true;
}

ApportionmentFunction * Apportionment::getApportionmentFunction() {
	return this->apportionment;
}

AggregationFunction * Apportionment::getAggregationFunction() {
	return this->aggregator;
}
