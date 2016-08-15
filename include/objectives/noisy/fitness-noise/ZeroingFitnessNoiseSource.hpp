#ifndef OBJECTIVES_NOISY_FITNESS_NOISE_ZeroingFitnessNoiseSource
#define OBJECTIVES_NOISY_FITNESS_NOISE_ZeroingFitnessNoiseSource

#include "FitnessNoiseSource.hpp"

class ZeroingFitnessNoiseSource: public FitnessNoiseSource {
	private:

	protected:
	double zeroChance;

	void init(double zeroChance);

	public:
	ZeroingFitnessNoiseSource(double zeroChance);

	float addNoise(float cleanFitness);
};

#endif
