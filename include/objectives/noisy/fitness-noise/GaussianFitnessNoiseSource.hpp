#include "FitnessNoiseSource.hpp"
#include <random>
#pragma once

class GaussianFitnessNoiseSource: public FitnessNoiseSource {
	private:

	protected:
	std::normal_distribution<double> modifierDist; 

	void init(double mean, double stdDev);

	public:
	GaussianFitnessNoiseSource(double stdDev);
	GaussianFitnessNoiseSource(double mean, double stdDev);
	GaussianFitnessNoiseSource(
		double mean,
		double stdDev,
		unsigned int seed
	);

	float addNoise(float cleanFitness);
};
