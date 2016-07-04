#include "../../core/NestedObjective.hpp"
#include "genetic-noise/GeneticNoiseSource.hpp"
#include "fitness-noise/FitnessNoiseSource.hpp"
#include <random>
#pragma once

class NoisyObjective: public NestedObjective {
	private:

	protected:
	GeneticNoiseSource * geneticSource;
	FitnessNoiseSource * fitnessSource;

	float addNoise(float cleanFitness);
	Genome addNoise(Genome * target);

	void init(
		GeneticNoiseSource * geneticSource,
		FitnessNoiseSource * fitnessSource
	);

	public:
	NoisyObjective(
		ObjectiveFunction * cleanObjective,
		GeneticNoiseSource * geneticSource
	);
	NoisyObjective(
		ObjectiveFunction * cleanObjective,
		FitnessNoiseSource * fitnessSource
	);
	NoisyObjective(
		ObjectiveFunction * cleanObjective,
		GeneticNoiseSource * geneticSource,
		FitnessNoiseSource * fitnessSource
	);
	float checkFitness(Genome * genome);
};
