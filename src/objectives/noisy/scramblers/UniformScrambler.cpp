#include "objectives/noisy/scramblers/UniformScrambler.hpp"

UniformScrambler::UniformScrambler(
	double mutationRate
) : GeneScrambler(new UniformMutation(mutationRate)) {}

UniformScrambler::UniformScrambler(
	double mutationRate,
	unsigned int seed
) : GeneScrambler(new UniformMutation(mutationRate, seed)) {}
