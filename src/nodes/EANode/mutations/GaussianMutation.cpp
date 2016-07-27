#include "nodes/EANode/mutations/GaussianMutation.hpp"
#include "core/HierRNG.hpp"
#include <chrono>
#include <random>

using namespace std;

GaussianMutation::GaussianMutation() : MutationOperation() {
	this->init(false);
}

GaussianMutation::GaussianMutation(
	bool endReflection
) : MutationOperation() {
	this->init(endReflection);
}

GaussianMutation::GaussianMutation(
	double mutationRate
) : MutationOperation(mutationRate) {
	this->init(false);
}

GaussianMutation::GaussianMutation(
	double mutationRate,
	bool endReflection
) : MutationOperation(mutationRate) {
	this->init(endReflection);
}

void GaussianMutation::init(bool endReflection) {
	this->endReflection = endReflection;
}

unsigned int GaussianMutation::getNewLocusValue(
	unsigned int currentValue,
	unsigned int largestPossibleValue
) {
	int addend = int(
		HierRNG::gaussianRandomNumber(0, largestPossibleValue/3)
	);
	int newValue = currentValue - addend;

	if (newValue < 0 && !this->endReflection) return 0;
	if (newValue < 0) return 0 - newValue;
	if (
		(unsigned int)newValue > largestPossibleValue
		&& !this->endReflection
	) return largestPossibleValue;

	if ((unsigned int)newValue > largestPossibleValue)
		return largestPossibleValue - (newValue-largestPossibleValue);

	return newValue;
}
