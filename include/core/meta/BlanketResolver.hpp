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
		Genome * blanket,
		PopulationNode * node
	);

	static void appendGenomes(
		std::vector<unsigned int> & targetGenes,
		std::vector<Locus*> & targetLoci,
		std::vector<unsigned int> genesToAppend,
		std::vector<Locus*> lociToAppend
	);

	static GenomeTemplate resolve(Genome * blanket, unsigned int target);

	protected:

	public:
	static unsigned int findHeadIndex(Genome * blanket);
	static Genome resolveBlanket(Genome * blanket);
};
