#include "../../core/NestedObjective.hpp"
#include "scramblers/GeneScrambler.hpp"
#include <random>
#pragma once

class NoisyObjective: public NestedObjective {
	private:

	protected:
	std::mt19937 generator;
	GeneScrambler * scrambler;

	virtual float addNoise(float cleanFitness)=0;
	Genome addNoise(Genome * target);

	void init(GeneScrambler * scrambler, unsigned int seed);

	public:
	NoisyObjective(ObjectiveFunction * cleanObjective);
	NoisyObjective(
		ObjectiveFunction * cleanObjective,
		GeneScrambler * scrambler
	);
	NoisyObjective(ObjectiveFunction * cleanObjective, unsigned int seed);
	NoisyObjective(
		ObjectiveFunction * cleanObjective,
		GeneScrambler * scrambler,
		unsigned int seed
	);
	float checkFitness(Genome * genome);
};
