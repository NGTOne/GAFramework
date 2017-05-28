#include "core/eval/Apportionment.hpp"
#include "core/utils/HierRNG.hpp"
#include "core/utils/HierGC.hpp"
#include <algorithm>

Apportionment::Apportionment(
	PopulationNode * upperNode,
	ApportionmentFunction * apportionment
) {
	// TODO: Empirically determine a sane default for try-on count
	this->init(
		upperNode,
		apportionment,
		upperNode->populationSize()
	);
}

Apportionment::Apportionment(
	PopulationNode * upperNode,
	ApportionmentFunction * apportionment,
	unsigned int tryOns
) {
	this->init(upperNode, apportionment, tryOns);
}

Apportionment::~Apportionment() {}

void Apportionment::registerInternalObjects() {
	ObjectiveFunction::registerInternalObjects();
	HierGC::registerObject(this->apportionment);
}

void Apportionment::init(
	PopulationNode * upperNode,
	ApportionmentFunction * apportionment,
	unsigned int tryOns
) {
	this->upperNode = upperNode;
	this->apportionment = apportionment;
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
	Genome* upper,
	Genome* rawUpper,
	Genome* target,
	Fitness upperFitness,
	std::vector<FitnessPair>& apportionedFitnesses
) {
	std::vector<unsigned int> componentIndices =
		this->getComponentIndices(upper, target);

	Genome* provider = this->getOperableGenome(upper);
	Genome flattened = target->flattenGenome();
	for (unsigned int i = 0; i < componentIndices.size(); i++)
		apportionedFitnesses.push_back(std::make_tuple(
			this->apportionment->apportionFitness(
				&flattened,
				provider,
				componentIndices[i],
				this->getRelevantIndices(
					target,
					componentIndices[i]
				),
				upperFitness
			),
			FitnessSource(rawUpper)
		));
	delete(provider);
}

bool Apportionment::upperGenomeUsesComponent(
	Genome * upper,
	Genome * target
) {
	return upper->usesComponent(target);
}

// TODO: Refactor this function
Fitness Apportionment::checkFitness(Genome* genome) {
	std::vector<FitnessPair> apportionedFitnesses;
	std::vector<bool> tried(this->upperNode->populationSize(), false);
	unsigned int triedOn = 0;

	for (unsigned int i = 0; i < this->upperNode->populationSize(); i++) {
		Genome* upper = this->upperNode->getIndex(i);
		if (this->upperGenomeUsesComponent(upper, genome)) {
			this->evaluatePair(
				upper,
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

		Genome* upper = this->upperNode
			->getIndex(untriedIndices[index]);
		Genome* provider = upper->replaceComponent(genome);
		this->evaluatePair(
			provider,
			upper,
			genome,
			this->upperNode->evaluateFitness(provider),
			apportionedFitnesses
		);
		delete(provider);
		untriedIndices.erase(untriedIndices.begin() + index);
		triedOn++;
	}

	return Fitness(this->postProcessFitnesses(apportionedFitnesses));
}

std::vector<FitnessPair> Apportionment::postProcessFitnesses(
	std::vector<FitnessPair> apportionedFitnesses
) {
	return apportionedFitnesses;
}

bool Apportionment::isApportioning() {
	return true;
}

ApportionmentFunction * Apportionment::getApportionmentFunction() {
	return this->apportionment;
}
