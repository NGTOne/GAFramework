#include "core/GenomeTemplate.hpp"
#include "exception/MismatchedCountsException.hpp"

GenomeTemplate::GenomeTemplate() : std::tuple<
	std::vector<unsigned int>,
	std::vector<Locus*>
>() {}

GenomeTemplate::GenomeTemplate(
	std::vector<unsigned int> genes,
	std::vector<Locus*> loci
) : std::tuple<std::vector<unsigned int>, std::vector<Locus*>>(genes, loci) {}

void GenomeTemplate::add(unsigned int gene, Locus * locus) {
	this->updateVector<0, unsigned int>(gene);
	this->updateVector<1, Locus*>(locus);
}

void GenomeTemplate::add(
	std::vector<unsigned int> genes,
	std::vector<Locus*> loci
) {
	if (genes.size() != loci.size()) throw MismatchedCountsException();

	for (unsigned int i = 0; i < genes.size(); i++)
		this->add(genes[i], loci[i]);
}

std::vector<unsigned int> GenomeTemplate::getGenes() {
	return std::get<0>(*this);
}

std::vector<Locus*> GenomeTemplate::getLoci() {
	return std::get<1>(*this);
}
