#include "GeneticNoiseSource.hpp"
#include "../../../mutations/UniformMutation.hpp"
#pragma once

class UniformGeneticNoiseSource: public GeneticNoiseSource {
	private:

	protected:

	public:
	UniformGeneticNoiseSource(double mutationRate);
	UniformGeneticNoiseSource(double mutationRate, unsigned int seed);
};
