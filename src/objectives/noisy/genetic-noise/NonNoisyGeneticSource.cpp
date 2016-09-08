#include "objectives/noisy/genetic-noise/NonNoisyGeneticSource.hpp"

NonNoisyGeneticSource::NonNoisyGeneticSource() : GeneticNoiseSource() {}

Genome NonNoisyGeneticSource::addNoise(Genome * target) {
	return Genome(target);
}
