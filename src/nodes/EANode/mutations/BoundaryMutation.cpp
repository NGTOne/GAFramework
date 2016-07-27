#include "nodes/EANode/mutations/BoundaryMutation.hpp"
#include "core/HierRNG.hpp"
#include <chrono>
#include <random>

using namespace std;

BoundaryMutation::BoundaryMutation() : MutationOperation() {}

BoundaryMutation::BoundaryMutation(
	double mutationRate
) : MutationOperation(mutationRate) {}

unsigned int BoundaryMutation::getNewLocusValue(
	unsigned int currentValue,
	unsigned int largestPossibleValue
) {
	unsigned int newValue = HierRNG::zeroOne<unsigned int>();
	return (newValue == 0 ? 0 : largestPossibleValue);
}
