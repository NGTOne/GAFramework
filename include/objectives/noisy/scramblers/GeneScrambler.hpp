#include <vector>
#include <random>
#pragma once

class GeneScrambler {
	private:

	protected:
	std::mt19937 generator;

	public:
	GeneScrambler();
	GeneScrambler(unsigned int seed);

	virtual std::vector<unsigned int> scramble(
		std::vector<unsigned int> genes
	)=0;
};
