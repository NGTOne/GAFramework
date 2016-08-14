#include "nodes/EANode/mutations/UniformMutation.hpp"
#include "core/utils/HierRNG.hpp"
#include <chrono>
#include <random>

UniformMutation::UniformMutation() : MutationOperation() {}

UniformMutation::UniformMutation(
	double mutationRate
) : MutationOperation(mutationRate) {}

Gene* UniformMutation::newLocusValue(Gene* current) {
	return current->copy(current->getLocus()->randomIndex());
}
