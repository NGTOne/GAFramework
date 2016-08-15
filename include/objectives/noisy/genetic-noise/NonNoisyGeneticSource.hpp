#ifndef OBJECTIVES_NOISY_GENETIC_NOISE_NonNoisyGeneticSource
#define OBJECTIVES_NOISY_GENETIC_NOISE_NonNoisyGeneticSource

#include "GeneticNoiseSource.hpp"

class NonNoisyGeneticSource: public GeneticNoiseSource {
	private:

	protected:

	public:
	NonNoisyGeneticSource();
	Genome addNoise(Genome * target);
};

#endif
