#include "FitnessNoiseSource.hpp"
#pragma once

class NonNoisyFitnessSource: public FitnessNoiseSource {
	private:

	protected:

	public:
	NonNoisyFitnessSource();

	float addNoise(float cleanFitness);
};
