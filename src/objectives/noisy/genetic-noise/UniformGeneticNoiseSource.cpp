#include "objectives/noisy/genetic-noise/UniformGeneticNoiseSource.hpp"

UniformGeneticNoiseSource::UniformGeneticNoiseSource(
	double mutationRate
) : GeneticNoiseSource(new UniformMutation(mutationRate)) {}

UniformGeneticNoiseSource::UniformGeneticNoiseSource(
	double mutationRate,
	unsigned int seed
) : GeneticNoiseSource(new UniformMutation(mutationRate, seed)) {}
