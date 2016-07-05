#include "../Genome.hpp"
#include "../GenomeTemplate.hpp"
#include "../Locus.hpp"
#include "../PopulationNode.hpp"
#include <vector>
#pragma once

class BlanketResolver {
	private:
	static std::vector<Genome*> getBlanketGenomes(Genome * blanket);

	static unsigned int findMetaComponentIndex(
		std::vector<Genome *> blanketGenomes,
		std::vector<bool> & usedGenomes,
		PopulationNode * node
	);

	static GenomeTemplate resolve(
		std::vector<Genome *> blanketGenomes,
		std::vector<bool> & usedGenomes,
		unsigned int target
	);

	protected:

	public:
	static std::vector<unsigned int> getIndices(
		Genome * blanket,
		Genome * target
	);
	static unsigned int findHeadIndex(Genome * blanket);
	static Genome resolveBlanket(Genome * blanket);
};
