#include "../Genome.hpp"
#include "../Locus.hpp"
#include "../PopulationNode.hpp"
#include <tuple>
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

	static std::tuple<
		std::vector<unsigned int>,
		std::vector<Locus*>
	> resolve(Genome * blanket, unsigned int target);

	protected:

	public:
	static unsigned int findHeadIndex(Genome * blanket);
	static Genome resolveBlanket(Genome * blanket);
};
