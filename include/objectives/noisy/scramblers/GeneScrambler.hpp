#include <vector>
#include <random>
#include "../../../nodes/EANode/MutationOperation.hpp"
#pragma once

class GeneScrambler {
	private:

	protected:
	MutationOperation * mutator;

	GeneScrambler();
	GeneScrambler(MutationOperation * mutator);

	public:
	~GeneScrambler();

	virtual Genome scramble(Genome * target);
	Genome scramble(Genome target);
};
