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

int BoundaryMutation::getNewLocusValue(
	int currentValue,
	int largestPossibleValue
) {
	uniform_int_distribution<int> newValueDist(0, 1);
	int newValue = newValueDist(generator);

	return (newValue == 0 ? 0 : largestPossibleValue);
}
