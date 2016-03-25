#include "mutations/UniformMutation.hpp"
#include <chrono>
#include <random>

using namespace std;

UniformMutation::UniformMutation() : MutationOperation() {}

UniformMutation::UniformMutation(
	double mutationRate
) : MutationOperation(mutationRate) {}

UniformMutation::UniformMutation(
	double mutationRate,
	unsigned seed
) : MutationOperation(mutationRate, seed) {}


int UniformMutation::getNewLocusValue(
	int currentValue,
	int largestPossibleValue
) {
	uniform_int_distribution<int> newValueDist(0, largestPossibleValue);
	int newValue = newValueDist(generator);

	return newValue;
}
