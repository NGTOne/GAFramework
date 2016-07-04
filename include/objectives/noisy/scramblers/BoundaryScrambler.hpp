#include "GeneScrambler.hpp"
#include "../../../mutations/BoundaryMutation.hpp"
#pragma once

class BoundaryScrambler: public GeneScrambler {
	private:

	protected:

	public:
	BoundaryScrambler(double mutationRate);
	BoundaryScrambler(double mutationRate, unsigned int seed);
};
