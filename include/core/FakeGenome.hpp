#include "Genome.hpp"
#pragma once

class FakeGenome : public Genome {
	private:

	protected:

	public:
	FakeGenome(std::vector<Gene*> genes, std::string speciesNode);
	FakeGenome(Genome* other);

	~FakeGenome();
};
