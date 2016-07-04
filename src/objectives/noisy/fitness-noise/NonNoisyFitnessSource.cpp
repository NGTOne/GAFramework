#include "objectives/noisy/fitness-noise/NonNoisyFitnessSource.hpp"

NonNoisyFitnessSource::NonNoisyFitnessSource() : FitnessNoiseSource() {}

NonNoisyFitnessSource::NonNoisyFitnessSource(
	unsigned int seed
) : FitnessNoiseSource(seed) {}

float NonNoisyFitnessSource::addNoise(float cleanFitness) {
	return cleanFitness;
}
