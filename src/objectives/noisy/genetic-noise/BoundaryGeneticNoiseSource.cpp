#include "objectives/noisy/genetic-noise/BoundaryGeneticNoiseSource.hpp"

BoundaryGeneticNoiseSource::BoundaryGeneticNoiseSource(
	double mutationRate
) : GeneticNoiseSource(new BoundaryMutation(mutationRate)) {}
