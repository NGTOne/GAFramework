#ifndef OBJECTIVES_NOISY_NoisyObjective
#define OBJECTIVES_NOISY_NoisyObjective

#include "../../core/eval/NestedObjective.hpp"
#include "genetic-noise/GeneticNoiseSource.hpp"
#include "fitness-noise/FitnessNoiseSource.hpp"
#include <random>

class NoisyObjective: public NestedObjective {
	private:

	protected:
	GeneticNoiseSource* geneticSource;
	FitnessNoiseSource* fitnessSource;

	Fitness addNoise(Fitness cleanFitness);
	Genome addNoise(Genome* target);

	void init(
		GeneticNoiseSource* geneticSource,
		FitnessNoiseSource* fitnessSource
	);

	public:
	NoisyObjective(
		ObjectiveFunction* cleanObjective,
		GeneticNoiseSource* geneticSource
	);
	NoisyObjective(
		ObjectiveFunction* cleanObjective,
		FitnessNoiseSource* fitnessSource
	);
	NoisyObjective(
		ObjectiveFunction* cleanObjective,
		GeneticNoiseSource* geneticSource,
		FitnessNoiseSource* fitnessSource
	);
	virtual void registerInternalObjects();

	Fitness checkFitness(Genome* genome);
};

#endif
