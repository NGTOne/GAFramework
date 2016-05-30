#include "mutations/GaussianMutation.hpp"
#include <chrono>
#include <random>

using namespace std;

GaussianMutation::GaussianMutation() : MutationOperation() {
	init(false);
}

GaussianMutation::GaussianMutation(
	bool reflection
) : MutationOperation() {
	init(reflection);
}

GaussianMutation::GaussianMutation(
	double mutationRate
) : MutationOperation(mutationRate) {
	init(false);
}

GaussianMutation::GaussianMutation(
	double mutationRate,
	bool reflection
) : MutationOperation(mutationRate) {
	init(reflection);
}

GaussianMutation::GaussianMutation(
	double mutationRate,
	unsigned seed
) : MutationOperation(mutationRate, seed) {
	init(false);
}

GaussianMutation::GaussianMutation(
	double mutationRate,
	bool reflection,
	unsigned seed
) : MutationOperation(mutationRate, seed) {
	init(reflection);
}

void GaussianMutation::init(bool reflection) {
	this->reflection = reflection;
}

unsigned int GaussianMutation::getNewLocusValue(
	unsigned int currentValue,
	unsigned int largestPossibleValue
) {
	normal_distribution<double> addendDist(0, largestPossibleValue/3);
	int addend = (int)addendDist(generator);
	int newValue = currentValue - addend;

	if (newValue < 0 && !this->reflection) return 0;
	if (newValue < 0) return 0 - newValue;
	if ((unsigned int)newValue > largestPossibleValue && !this->reflection)
		return largestPossibleValue;
	if ((unsigned int)newValue > largestPossibleValue)
		return largestPossibleValue - (newValue-largestPossibleValue);

	return newValue;
}
