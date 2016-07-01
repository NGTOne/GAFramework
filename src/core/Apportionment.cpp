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

	Genome * provider = this->getOperableGenome(upper);
	Genome flattened = target->flattenGenome();
	for (unsigned int i = 0; i < componentIndices.size(); i++)
		apportionedFitnesses.push_back(
			this->apportionment->apportionFitness(
				&flattened,
				provider,
				componentIndices[i],
				upperFitness
			)
		);
	delete(provider);
}

// TODO: Refactor this function
int Apportionment::checkFitness(Genome * genome) {
	std::vector<int> apportionedFitnesses;
	std::vector<bool> tried(this->upperNode->populationSize(), false);
	unsigned int triedOn = 0;

	for (unsigned int i = 0; i < this->upperNode->populationSize(); i++)
		if (this->upperNode->getIndex(i)->usesComponent(genome)) {
			this->evaluatePair(
				this->upperNode->getIndex(i),
				genome,
				this->upperNode->getFitnessAtIndex(i),
				apportionedFitnesses
			);
			triedOn++;
			tried[i] = true;
		}

	std::vector<unsigned int> untriedIndices;
	for (unsigned int i = 0; i < tried.size(); i++)
		if (!tried[i]) untriedIndices.push_back(i);

	// TODO: Refactor this into the class def
	mt19937 generator;

	unsigned int realTryOns = std::min(
		this->upperNode->populationSize(),
		this->tryOns
	);

	unsigned int index;
	while (triedOn < realTryOns) {
		uniform_int_distribution<unsigned int> selDist(
			0,
			untriedIndices.size() - 1
		);
		index = selDist(generator);

		Genome * provider = this->upperNode
			->getIndex(untriedIndices[index])
			->replaceComponent(genome);
		this->evaluatePair(
			provider,
			genome,
			this->upperNode->evaluateFitness(provider),
			apportionedFitnesses
		);
		delete(provider);
		untriedIndices.erase(untriedIndices.begin() + index);
		triedOn++;
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
