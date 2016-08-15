#ifndef CORE_FakeGenome
#define CORE_FakeGenome

#include "Genome.hpp"

class FakeGenome : public Genome {
	private:

	protected:

	public:
	FakeGenome(std::vector<Gene*> genes, std::string speciesNode);
	FakeGenome(Genome* other);

	~FakeGenome();
};

#endif
