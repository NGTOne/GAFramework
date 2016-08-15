#ifndef OBJECTIVES_NOISY_GENETIC_NOISE_UniformGeneticNoiseSource
#define OBJECTIVES_NOISY_GENETIC_NOISE_UniformGeneticNoiseSource

#include "GeneticNoiseSource.hpp"
#include "../../../nodes/EANode/mutations/UniformMutation.hpp"

class UniformGeneticNoiseSource: public GeneticNoiseSource {
	private:

	protected:

	public:
	UniformGeneticNoiseSource(double mutationRate);
};

#endif
