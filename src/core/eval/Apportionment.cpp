#include "core/eval/Apportionment.hpp"
#include "core/utils/HierRNG.hpp"
#include "core/utils/HierGC.hpp"
#include <algorithm>

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

void Apportionment::registerInternalObjects() {
	ObjectiveFunction::registerInternalObjects();
	HierGC::registerObject(this->apportionment);
	HierGC::registerObject(this->aggregator);
}

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

std::vector<unsigned int> Apportionment::getRelevantIndices(
	Genome * target,
	unsigned int targetIndex
) {
	unsigned int length = target->flattenedGenomeLength();
	std::vector<unsigned int> indices;
	for (unsigned int i = 0; i < length; i++)
		indices.push_back(targetIndex + i);

	return indices;
}

void Apportionment::evaluatePair(
	Genome * upper,
	Genome * target,
	float upperFitness,
	std::vector<float> & apportionedFitnesses
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
				this->getRelevantIndices(
					target,
					componentIndices[i]
				),
				upperFitness
			)
		);
	delete(provider);
}

bool Apportionment::upperGenomeUsesComponent(
	Genome * upper,
	Genome * target
) {
	return upper->usesComponent(target);
}

// TODO: Refactor this function
float Apportionment::checkFitness(Genome * genome) {
	std::vector<float> apportionedFitnesses;
	std::vector<bool> tried(this->upperNode->populationSize(), false);
	unsigned int triedOn = 0;

	for (unsigned int i = 0; i < this->upperNode->populationSize(); i++) {
		Genome * upper = this->upperNode->getIndex(i);
		if (this->upperGenomeUsesComponent(upper, genome)) {
			this->evaluatePair(
				upper,
				genome,
				this->upperNode->getFitnessAtIndex(i),
				apportionedFitnesses
			);
			triedOn++;
			tried[i] = true;
		}
	}

	std::vector<unsigned int> untriedIndices;
	for (unsigned int i = 0; i < tried.size(); i++)
		if (!tried[i]) untriedIndices.push_back(i);

	unsigned int realTryOns = std::min(
		this->upperNode->populationSize(),
		this->tryOns
	);

	unsigned int index;
	while (triedOn < realTryOns) {
		index = HierRNG::index(untriedIndices.size() - 1);

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

float Apportionment::aggregateFitnesses(
	std::vector<float> apportionedFitnesses
) {
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
