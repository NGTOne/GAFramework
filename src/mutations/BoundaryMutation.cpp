#include "mutations/BoundaryMutation.hpp"
#include <chrono>
#include <random>

using namespace std;

BoundaryMutation::BoundaryMutation() : MutationOperation() {}

BoundaryMutation::BoundaryMutation(
	double mutationRate
) : MutationOperation(mutationRate) {}

BoundaryMutation::BoundaryMutation(
	double mutationRate,
	unsigned seed
) : MutationOperation(mutationRate, seed) {}

unsigned int BoundaryMutation::getNewLocusValue(
	unsigned int currentValue,
	unsigned int largestPossibleValue
) {
	uniform_int_distribution<unsigned int> newValueDist(0, 1);
	unsigned int newValue = newValueDist(generator);

	return (newValue == 0 ? 0 : largestPossibleValue);
}
