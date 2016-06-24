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

std::vector<unsigned int> Apportionment::getComponentIndices(
	Genome * upper,
	Genome * target
) {
	return upper->getFlattenedIndices(target);
}

void Apportionment::evaluatePair(
	Genome * upper,
	Genome * target,
	int upperFitness,
	std::vector<int> & apportionedFitnesses
) {
	std::vector<unsigned int> componentIndices =
		this->getComponentIndices(upper, target);

	for (unsigned int i = 0; i < componentIndices.size(); i++) {
		Genome * provider = this->getOperableGenome(upper);
		apportionedFitnesses.push_back(
			this->apportionment->apportionFitness(
				target,
				provider,
				componentIndices[i],
				upperFitness
			)
		);
		delete(provider);
	}
}

// TODO: Refactor this function
int Apportionment::checkFitness(Genome * genome) {
	std::vector<int> apportionedFitnesses;
	std::vector<bool> tried(this->upperNode->populationSize(), false);
	unsigned int triedOn = 0;
	Genome flattened = genome->flattenGenome();

	for (unsigned int i = 0; i < this->upperNode->populationSize(); i++) {
		if (this->upperNode->getIndex(i)->usesComponent(genome)) {
			this->evaluatePair(
				this->upperNode->getIndex(i),
				&flattened,
				this->upperNode->getFitnessAtIndex(i),
				apportionedFitnesses
			);
			triedOn++;
			tried[i] = true;
		}
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
		this->evaluatePair(
			&provider,
			&flattened,
			this->upperNode->evaluateFitness(&provider),
			apportionedFitnesses
		);
		triedOn++;
		tried[index] = true;
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
