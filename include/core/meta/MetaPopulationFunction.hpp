#include "../Genome.hpp"
#include "../Locus.hpp"
#include "../PopulationNode.hpp"
#include <tuple>
#include <vector>
#pragma once

class MetaPopulationFunction {
	private:
	std::vector<Genome*> getBlanketGenomes(Genome * blanket);

	unsigned int findHeadIndex(Genome * blanket);
	unsigned int findMetaComponentIndex(
		Genome * blanket,
		PopulationNode * node
	);

	void appendGenomes(
		std::vector<unsigned int> & targetGenes,
		std::vector<Locus*> & targetLoci,
		std::vector<unsigned int> genesToAppend,
		std::vector<Locus*> lociToAppend
	);

	std::tuple<
		std::vector<unsigned int>,
		std::vector<Locus*>
	> resolve(Genome * blanket, unsigned int target);

	protected:
	Genome resolveBlanket(Genome * blanket);

	public:
};
