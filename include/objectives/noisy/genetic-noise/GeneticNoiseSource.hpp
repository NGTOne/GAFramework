#include <vector>
#include <random>
#include "../../../nodes/EANode/MutationOperation.hpp"
#pragma once

class GeneticNoiseSource {
	private:

	protected:
	MutationOperation * mutator;

	GeneticNoiseSource();
	GeneticNoiseSource(MutationOperation * mutator);

	public:
	~GeneticNoiseSource();

	virtual Genome addNoise(Genome * target);
	Genome addNoise(Genome target);
};
