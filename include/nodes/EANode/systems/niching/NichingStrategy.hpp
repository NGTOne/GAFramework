#pragma once
#include "../../../../core/Genome.hpp"
#include <vector>

class NichingStrategy {
	private:

	protected:

	public:
	virtual ~NichingStrategy();

	virtual std::vector<unsigned int> getIndices(
		std::vector<Genome*> initialPopulation,
		std::vector<Genome*> newPopulation
	)=0;
};