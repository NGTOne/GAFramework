#include "objectives/noisy/genetic-noise/BoundaryGeneticNoiseSource.hpp"

BoundaryGeneticNoiseSource::BoundaryGeneticNoiseSource(
	double mutationRate
) : GeneticNoiseSource(new BoundaryMutation(mutationRate)) {}

BoundaryGeneticNoiseSource::BoundaryGeneticNoiseSource(
	double mutationRate,
	unsigned int seed
) : GeneticNoiseSource(new BoundaryMutation(mutationRate, seed)) {}
