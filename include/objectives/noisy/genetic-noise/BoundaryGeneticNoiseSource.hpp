#include "GeneticNoiseSource.hpp"
#include "../../../mutations/BoundaryMutation.hpp"
#pragma once

class BoundaryGeneticNoiseSource: public GeneticNoiseSource {
	private:

	protected:

	public:
	BoundaryGeneticNoiseSource(double mutationRate);
	BoundaryGeneticNoiseSource(double mutationRate, unsigned int seed);
};
