#ifndef OBJECTIVES_NOISY_GENETIC_NOISE_BoundaryGeneticNoiseSource
#define OBJECTIVES_NOISY_GENETIC_NOISE_BoundaryGeneticNoiseSource

#include "GeneticNoiseSource.hpp"
#include "../../../nodes/EANode/mutations/BoundaryMutation.hpp"

class BoundaryGeneticNoiseSource: public GeneticNoiseSource {
	private:

	protected:

	public:
	BoundaryGeneticNoiseSource(double mutationRate);
};

#endif
