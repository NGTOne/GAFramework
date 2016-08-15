#ifndef OBJECTIVES_NOISY_FITNESS_NOISE_NonNoisyFitnessSource
#define OBJECTIVES_NOISY_FITNESS_NOISE_NonNoisyFitnessSource

#include "FitnessNoiseSource.hpp"

class NonNoisyFitnessSource: public FitnessNoiseSource {
	private:

	protected:

	public:
	NonNoisyFitnessSource();

	float addNoise(float cleanFitness);
};

#endif
