#include "core/meta/BlanketResolver.hpp"
#include "core/PopulationNode.hpp"
#include "core/Locus.hpp"
#include "loci/PopulationLocus.hpp"
#include "exception/InvalidBlanketException.hpp"

std::vector<Genome*> BlanketResolver::getBlanketGenomes(
	Genome * blanket
) {
	std::vector<Genome*> blanketGenomes;
	for (unsigned int i = 0; i < blanket->genomeLength(); i++)
		blanketGenomes.push_back(blanket->getIndex<Genome*>(i));

	return blanketGenomes;
}

#include <iostream>

unsigned int BlanketResolver::findHeadIndex(Genome * blanket) {
	std::vector<bool> matched(blanket->genomeLength(), false);
	std::vector<Genome*> blanketGenomes =
		BlanketResolver::getBlanketGenomes(blanket);
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

// TODO: Make sure this works for more complex structures (where node is
// repeated)
unsigned int BlanketResolver::findMetaComponentIndex(
	Genome * blanket,
	PopulationNode * node
) {
	std::vector<Genome*> blanketGenomes =
		BlanketResolver::getBlanketGenomes(blanket);

	for (unsigned int i = 0; i < blanketGenomes.size(); i++)
		if (node->usesSpecies(blanketGenomes[i]))
			return i;

	// Should never get here
	throw InvalidBlanketException();
}

void BlanketResolver::appendGenomes(
	std::vector<unsigned int> & targetGenes,
	std::vector<Locus*> & targetLoci,
	std::vector<unsigned int> genesToAppend,
	std::vector<Locus*> lociToAppend
) {
	for (unsigned int i = 0; i < genesToAppend.size(); i++) {
		targetGenes.push_back(genesToAppend[i]);
		targetLoci.push_back(lociToAppend[i]);
	}
}

GenomeTemplate BlanketResolver::resolve(
	Genome * blanket,
	unsigned int target
) {
	std::vector<unsigned int> resolvedGenes;
	std::vector<Locus*> resolvedLoci;

	Genome * toResolve = blanket->getIndex<Genome*>(target);

	std::vector<unsigned int> unresolvedGenes = toResolve->getGenome();
	std::vector<Locus*> unresolvedLoci = toResolve->getLoci();
	for (unsigned int i = 0; i < toResolve->genomeLength(); i++) {
		if (!unresolvedLoci[i]->isConstructive()) {
			resolvedGenes.push_back(unresolvedGenes[i]);
			resolvedLoci.push_back(unresolvedLoci[i]);
		} else {
			std::vector<unsigned int> resolvedComponentGenes;
			std::vector<Locus*> resolvedComponentLoci;
			std::tie(
				resolvedComponentGenes,
				resolvedComponentLoci
			) = BlanketResolver::resolve(
				blanket,
				BlanketResolver::findMetaComponentIndex(
					blanket,
					((PopulationLocus*)unresolvedLoci[i])
						->getNode()
				)
			);
			BlanketResolver::appendGenomes(
				resolvedGenes,
				resolvedLoci,
				resolvedComponentGenes,
				resolvedComponentLoci
			);
		}
	}

	return GenomeTemplate(resolvedGenes, resolvedLoci);
}

Genome BlanketResolver::resolveBlanket(Genome * blanket) {
	std::vector<Locus*> resolvedLoci;
	std::vector<unsigned int> resolvedGenes;
	unsigned int head = BlanketResolver::findHeadIndex(blanket);
	std::tie(resolvedGenes, resolvedLoci) =
		BlanketResolver::resolve(blanket, head);
	return Genome(
		resolvedGenes,
		resolvedLoci,
		blanket->getIndex<Genome*>(head)->getSpeciesNode()
	);
}
