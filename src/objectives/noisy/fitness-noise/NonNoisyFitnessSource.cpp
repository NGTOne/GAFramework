#include "objectives/noisy/fitness-noise/NonNoisyFitnessSource.hpp"

NonNoisyFitnessSource::NonNoisyFitnessSource() : FitnessNoiseSource() {}

Fitness NonNoisyFitnessSource::addNoise(Fitness cleanFitness) {
	return cleanFitness;
}
