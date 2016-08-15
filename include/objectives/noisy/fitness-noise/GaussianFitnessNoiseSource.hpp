#ifndef OBJECTIVES_NOISY_FITNESS_NOISE_GaussianFitnessNoiseSource
#define OBJECTIVES_NOISY_FITNESS_NOISE_GaussianFitnessNoiseSource

#include "FitnessNoiseSource.hpp"

class GaussianFitnessNoiseSource: public FitnessNoiseSource {
	private:

	protected:
	double mean;
	double stdDev;

	void init(double mean, double stdDev);

	public:
	GaussianFitnessNoiseSource(double stdDev);
	GaussianFitnessNoiseSource(double mean, double stdDev);

	float addNoise(float cleanFitness);
};

#endif
