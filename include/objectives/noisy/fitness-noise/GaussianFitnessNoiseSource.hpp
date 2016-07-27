#include "FitnessNoiseSource.hpp"
#include <random>
#pragma once

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
