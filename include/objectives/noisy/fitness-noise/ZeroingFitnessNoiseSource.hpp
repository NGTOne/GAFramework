#include "FitnessNoiseSource.hpp"
#pragma once

class ZeroingFitnessNoiseSource: public FitnessNoiseSource {
	private:

	protected:
	std::uniform_real_distribution<double> modifierDist;
	double zeroChance;

	void init(double zeroChance);

	public:
	ZeroingFitnessNoiseSource(double zeroChance);
	ZeroingFitnessNoiseSource(double zeroChance, unsigned int seed);

	float addNoise(float cleanFitness);
};
