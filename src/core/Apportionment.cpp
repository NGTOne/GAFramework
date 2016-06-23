#include "core/Apportionment.hpp"
#include <algorithm>
#include <random>

Apportionment::Apportionment(
	PopulationNode * upperNode,
	ApportionmentFunction * apportionment,
	AggregationFunction * aggregator
) {
	// TODO: Empirically determine a sane default for try-on count
	this->init(
		upperNode,
		apportionment,
		aggregator,
		upperNode->populationSize()
	);
}

Apportionment::Apportionment(
	PopulationNode * upperNode,
	ApportionmentFunction * apportionment,
	AggregationFunction * aggregator,
	unsigned int tryOns
) {
	this->init(upperNode, apportionment, aggregator, tryOns);
}

Apportionment::~Apportionment() {}

void Apportionment::init(
	PopulationNode * upperNode,
	ApportionmentFunction * apportionment,
	AggregationFunction * aggregator,
	unsigned int tryOns
) {
	this->upperNode = upperNode;
	this->apportionment = apportionment;
	this->aggregator = aggregator;
	this->tryOns = tryOns;
}

Genome * Apportionment::getOperableGenome(Genome * genome) {
	return new Genome(genome->flattenGenome());
}

// TODO: Refactor this function
int Apportionment::checkFitness(Genome * genome) {
	std::vector<int> apportionedFitnesses;
	std::vector<bool> tried(this->upperNode->populationSize(), false);
	unsigned int triedOn = 0;

	for (unsigned int i = 0; i < this->upperNode->populationSize(); i++) {
		Genome * provider = this->getOperableGenome(
			this->upperNode->getIndex(i)
		);
		if (provider->usesComponent(genome)) {
			apportionedFitnesses.push_back(
				this->apportionment->apportionFitness(
					genome,
					provider,
					this->upperNode->getFitnessAtIndex(i)
				)
			);
			triedOn++;
			tried[i] = true;
		}
		delete(provider);
	}

	// TODO: Refactor this into the class def
	mt19937 generator;
	uniform_int_distribution<unsigned int> selDist(
		0,
		this->upperNode->populationSize()
	);

	unsigned int tryOns = std::min(
		this->upperNode->populationSize(),
		this->tryOns
	);

	while (triedOn < tryOns) {
		unsigned int index;
		do index = selDist(generator); while(tried[index]);
		Genome provider = this->upperNode->getIndex(index)
			->replaceComponent(genome);
		Genome * operable = this->getOperableGenome(&provider);
		apportionedFitnesses.push_back(
			this->apportionment->apportionFitness(
				genome,
				operable,
				this->upperNode->evaluateFitness(&provider)
			)
		);
		triedOn++;
		tried[index] = true;
		delete(operable);
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
