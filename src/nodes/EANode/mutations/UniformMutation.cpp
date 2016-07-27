#include "nodes/EANode/mutations/UniformMutation.hpp"
#include "core/HierRNG.hpp"
#include <chrono>
#include <random>

using namespace std;

UniformMutation::UniformMutation() : MutationOperation() {}

UniformMutation::UniformMutation(
	double mutationRate
) : MutationOperation(mutationRate) {}

unsigned int UniformMutation::getNewLocusValue(
	unsigned int currentValue,
	unsigned int largestPossibleValue
) {
	return HierRNG::uniformRandomNumber<
		unsigned int
	>(0, largestPossibleValue);
}
