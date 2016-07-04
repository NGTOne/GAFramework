#include <random>
#pragma once

class FitnessNoiseSource {
	private:

	protected:
	std::mt19937 generator;

	FitnessNoiseSource();
	FitnessNoiseSource(unsigned int seed);

	public:
	virtual float addNoise(float cleanFitness)=0;
};
