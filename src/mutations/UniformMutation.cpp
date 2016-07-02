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
	unsigned int seed
) : MutationOperation(mutationRate, seed) {}


unsigned int UniformMutation::getNewLocusValue(
	unsigned int currentValue,
	unsigned int largestPossibleValue
) {
	uniform_int_distribution<unsigned int> newValueDist(
		0,
		largestPossibleValue
	);
	return newValueDist(generator);
}
