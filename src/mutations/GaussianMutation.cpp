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

int GaussianMutation::getNewLocusValue(
	int currentValue,
	int largestPossibleValue
) {
	normal_distribution<double> addendDist(0, largestPossibleValue/3);
	int addend = (int)addendDist(generator);
	int newValue = currentValue - addend;
	int borderValue = (newValue < 0 ? 0 : largestPossibleValue);

	if (newValue < 0 || newValue > largestPossibleValue) {
		if (reflection) {
			addend = -(
				newValue < 0 ? 
				newValue : 
				newValue - largestPossibleValue
			);
			newValue = borderValue + addend;
		} else {
			newValue = borderValue;
		}
	}

	return newValue;
}
