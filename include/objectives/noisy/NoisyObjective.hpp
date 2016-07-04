#include "../../core/NestedObjective.hpp"
#include "genetic-noise/GeneticNoiseSource.hpp"
#include <random>
#pragma once

class NoisyObjective: public NestedObjective {
	private:

	protected:
	std::mt19937 generator;
	GeneticNoiseSource * geneticSource;

	virtual float addNoise(float cleanFitness)=0;
	Genome addNoise(Genome * target);

	void init(GeneticNoiseSource * geneticSource, unsigned int seed);

	public:
	NoisyObjective(ObjectiveFunction * cleanObjective);
	NoisyObjective(
		ObjectiveFunction * cleanObjective,
		GeneticNoiseSource * geneticSource
	);
	NoisyObjective(ObjectiveFunction * cleanObjective, unsigned int seed);
	NoisyObjective(
		ObjectiveFunction * cleanObjective,
		GeneticNoiseSource * geneticSource,
		unsigned int seed
	);
	float checkFitness(Genome * genome);
};
