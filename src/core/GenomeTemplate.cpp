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

GenomeTemplate GenomeTemplate::add(unsigned int gene, Locus * locus) {
	this->updateVector<0, unsigned int>(gene);
	this->updateVector<1, Locus*>(locus);
	return *this;
}

GenomeTemplate GenomeTemplate::add(std::tuple<unsigned int, Locus*> newGene) {
	this->add(std::get<0>(newGene), std::get<1>(newGene));
	return *this;
}

GenomeTemplate GenomeTemplate::add(
	std::vector<unsigned int> genes,
	std::vector<Locus*> loci
) {
	if (genes.size() != loci.size()) throw MismatchedCountsException();

	for (unsigned int i = 0; i < genes.size(); i++)
		this->add(genes[i], loci[i]);
	return *this;
}

GenomeTemplate GenomeTemplate::add(GenomeTemplate other) {
	this->add(other.getGenes(), other.getLoci());
	return *this;
}

GenomeTemplate GenomeTemplate::set(unsigned int value, unsigned int index) {
	this->updateVector<0, unsigned int>(value, index);
	return *this;
}

GenomeTemplate GenomeTemplate::set(Locus * locus, unsigned int index) {
	this->updateVector<1, Locus*>(locus, index);
	return *this;
}

GenomeTemplate GenomeTemplate::set(
	unsigned int value,
	Locus * locus,
	unsigned int index
) {
	this->set(value, index);
	this->set(locus, index);
	return *this;
}

std::vector<unsigned int> GenomeTemplate::getGenes() {
	return std::get<0>(*this);
}

std::vector<Locus*> GenomeTemplate::getLoci() {
	return std::get<1>(*this);
}

unsigned int GenomeTemplate::getGene(unsigned int index) {
	return std::get<0>(this->getIndex(index));
}

Locus * GenomeTemplate::getLocus(unsigned int index) {
	return std::get<1>(this->getIndex(index));
}

std::tuple<unsigned int, Locus*> GenomeTemplate::getIndex(unsigned int index) {
	return std::make_tuple(
		this->getGenes()[index],
		this->getLoci()[index]
	);
}

unsigned int GenomeTemplate::genomeLength() {
	return this->getGenes().size();
}
