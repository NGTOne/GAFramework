#include "GeneScrambler.hpp"
#include "../../../mutations/UniformMutation.hpp"
#pragma once

class UniformScrambler: public GeneScrambler {
	private:

	protected:

	public:
	UniformScrambler(double mutationRate);
	UniformScrambler(double mutationRate, unsigned int seed);
};
