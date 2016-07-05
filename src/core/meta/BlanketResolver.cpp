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
	std::vector<Genome *> blanketGenomes,
	std::vector<bool> & usedGenomes,
	PopulationNode * node
) {
	for (unsigned int i = 0; i < blanketGenomes.size(); i++)
		if (!usedGenomes[i] && node->usesSpecies(blanketGenomes[i])) {
			usedGenomes[i] = true;
			return i;
		}

	// Should never get here
	throw InvalidBlanketException();
}

#include <iostream>

std::vector<unsigned int> BlanketResolver::getIndices(
	Genome * blanket,
	Genome * target
) {
	std::vector<unsigned int> indices;
	unsigned int currentIndex = 0;
	for (unsigned int i = 0; i < blanket->genomeLength(); i++) {
		Genome * temp = blanket->getIndex<Genome*>(i);
		if (temp == target) indices.push_back(currentIndex);
		if (temp->isSameSpecies(target)) currentIndex++;
	}

	return indices;
}

GenomeTemplate BlanketResolver::resolve(
	std::vector<Genome *> blanketGenomes,
	std::vector<bool> & usedGenomes,
	unsigned int target
) {
	GenomeTemplate resolved;
	GenomeTemplate unresolved = blanketGenomes[target]->getTemplate();

	for (unsigned int i = 0; i < unresolved.genomeLength(); i++) {
		Locus * temp = unresolved.getLocus(i);
		if (!temp->isConstructive()) {
			resolved.add(unresolved.getIndex(i));
		} else {
			resolved.add(BlanketResolver::resolve(
				blanketGenomes,
				usedGenomes,
				BlanketResolver::findMetaComponentIndex(
					blanketGenomes,
					usedGenomes,
					((PopulationLocus*)temp)->getNode()
				)
			));
		}
	}

	return resolved;
}

Genome BlanketResolver::resolveBlanket(Genome * blanket) {
	unsigned int head = BlanketResolver::findHeadIndex(blanket);
	std::vector<bool> used(blanket->genomeLength(), false);
	return Genome(
		BlanketResolver::resolve(
			BlanketResolver::getBlanketGenomes(blanket),
			used,
			head
		),
		blanket->getIndex<Genome*>(head)->getSpeciesNode()
	);
}
