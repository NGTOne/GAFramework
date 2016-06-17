#include "core/meta/MetaPopulationFunction.hpp"
#include "core/PopulationNode.hpp"
#include "core/Locus.hpp"
#include "loci/PopulationLocus.hpp"
#include "exception/InvalidBlanketException.hpp"

unsigned int MetaPopulationFunction::findHeadIndex(Genome * blanket) {
	std::vector<bool> matched(blanket->genomeLength(), false);
	std::vector<Genome*> blanketGenomes;

	for (unsigned int i = 0; i < blanket->genomeLength(); i++)
		blanketGenomes.push_back(blanket->getIndex<Genome*>(i));

	std::vector<PopulationNode*> nodes;
	for (unsigned int i = 0; i < blanket->genomeLength(); i++) {
		std::set<Locus*> constructiveLoci =
			blanketGenomes[i]->getConstructiveLoci();

		for (auto locus : constructiveLoci)
			nodes.push_back(((PopulationLocus*)locus)->getNode());
	}

	for (unsigned int i = 0; i < blanketGenomes.size(); i++)
		for (unsigned int k = 0; k < nodes.size(); k++)
			if (nodes[k]->contains(blanketGenomes[i])) {
				matched[i] = true;
				break;
			}

	for (unsigned int i = 0; i < matched.size(); i++)
		if (!matched[i]) return i;

	// Strangeness is happening here
	throw InvalidBlanketException();
}

Genome MetaPopulationFunction::resolveBlanket(Genome * blanket) {
	std::vector<Locus*> resolvedLoci;
	std::vector<unsigned int> resolvedGenes;
}
