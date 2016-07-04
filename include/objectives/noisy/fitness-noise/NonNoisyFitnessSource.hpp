#include "FitnessNoiseSource.hpp"
#pragma once

class NonNoisyFitnessSource: public FitnessNoiseSource {
	private:

	protected:

	public:
	NonNoisyFitnessSource();
	NonNoisyFitnessSource(unsigned int seed);

	float addNoise(float cleanFitness);
};
