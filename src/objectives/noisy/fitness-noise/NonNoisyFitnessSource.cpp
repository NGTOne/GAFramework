#include "objectives/noisy/fitness-noise/NonNoisyFitnessSource.hpp"

NonNoisyFitnessSource::NonNoisyFitnessSource() : FitnessNoiseSource() {}

float NonNoisyFitnessSource::addNoise(float cleanFitness) {
	return cleanFitness;
}
