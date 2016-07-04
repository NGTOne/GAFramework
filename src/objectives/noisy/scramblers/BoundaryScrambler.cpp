#include "objectives/noisy/scramblers/BoundaryScrambler.hpp"

BoundaryScrambler::BoundaryScrambler(
	double mutationRate
) : GeneScrambler(new BoundaryMutation(mutationRate)) {}

BoundaryScrambler::BoundaryScrambler(
	double mutationRate,
	unsigned int seed
) : GeneScrambler(new BoundaryMutation(mutationRate, seed)) {}
