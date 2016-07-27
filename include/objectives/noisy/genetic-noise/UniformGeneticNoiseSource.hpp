#include "GeneticNoiseSource.hpp"
#include "../../../nodes/EANode/mutations/UniformMutation.hpp"
#pragma once

class UniformGeneticNoiseSource: public GeneticNoiseSource {
	private:

	protected:

	public:
	UniformGeneticNoiseSource(double mutationRate);
};
