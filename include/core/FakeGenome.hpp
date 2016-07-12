#include "Genome.hpp"
#pragma once

class FakeGenome : public Genome {
	private:

	protected:

	public:
	FakeGenome(
		std::vector<unsigned int> genes,
		std::vector<Locus *> loci,
		std::string speciesNode
	);
	FakeGenome(Genome * other);

	~FakeGenome();
};
