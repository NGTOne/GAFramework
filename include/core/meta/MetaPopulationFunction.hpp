#include "../Genome.hpp"
#pragma once

class MetaPopulationFunction {
	private:
	unsigned int findHeadIndex(Genome * blanket);

	protected:
	Genome resolveBlanket(Genome * blanket);

	public:
};
