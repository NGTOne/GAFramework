#include "nodes/EANode/mutations/BoundaryMutation.hpp"
#include "core/utils/HierRNG.hpp"
#include <chrono>
#include <random>

BoundaryMutation::BoundaryMutation() : MutationOperation() {}

BoundaryMutation::BoundaryMutation(
	double mutationRate
) : MutationOperation(mutationRate) {}

Gene* BoundaryMutation::newLocusValue(Gene* current) {
	Locus* locus = current->getLocus();
	return current->copy(
		HierRNG::binary() ? locus->bottomIndex() : locus->topIndex()
	);
}
