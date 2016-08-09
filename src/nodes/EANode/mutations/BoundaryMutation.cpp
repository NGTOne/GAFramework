#include "nodes/EANode/mutations/BoundaryMutation.hpp"
#include "core/HierRNG.hpp"
#include <chrono>
#include <random>

using namespace std;

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
