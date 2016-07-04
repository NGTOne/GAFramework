#include "GeneticNoiseSource.hpp"
#pragma once

class NonNoisyGeneticSource: public GeneticNoiseSource {
	private:

	protected:

	public:
	NonNoisyGeneticSource();
	Genome addNoise(Genome * target);
};
