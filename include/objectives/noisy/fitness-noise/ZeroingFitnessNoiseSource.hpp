#include "FitnessNoiseSource.hpp"
#pragma once

class ZeroingFitnessNoiseSource: public FitnessNoiseSource {
	private:

	protected:
	double zeroChance;

	void init(double zeroChance);

	public:
	ZeroingFitnessNoiseSource(double zeroChance);

	float addNoise(float cleanFitness);
};
