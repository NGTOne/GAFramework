#include "GeneScrambler.hpp"
#pragma once

class NonScrambler: public GeneScrambler {
	private:

	protected:

	public:
	NonScrambler();
	Genome scramble(Genome * target);
};
