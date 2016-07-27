#include "objectives/noisy/genetic-noise/UniformGeneticNoiseSource.hpp"

UniformGeneticNoiseSource::UniformGeneticNoiseSource(
	double mutationRate
) : GeneticNoiseSource(new UniformMutation(mutationRate)) {}
