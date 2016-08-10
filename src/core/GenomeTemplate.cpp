#include "core/GenomeTemplate.hpp"
#include "exception/MismatchedCountsException.hpp"

GenomeTemplate::GenomeTemplate() {}

GenomeTemplate::GenomeTemplate(
	std::vector<double> genes,
	std::vector<Locus*> loci
) {
	if (genes.size() != loci.size()) throw MismatchedCountsException();
	for (unsigned int i = 0; i < genes.size(); i++)
		this->genes.push_back(loci[i]->getGene(genes[i]));
}

GenomeTemplate::GenomeTemplate(std::vector<Gene*> genes) {
	for (unsigned int i = 0; i < genes.size(); i++)
		this->genes.push_back(genes[i]->copy());
}

GenomeTemplate GenomeTemplate::add(double gene, Locus* locus) {
	this->genes.push_back(locus->getGene(gene));
	return *this;
}

GenomeTemplate GenomeTemplate::add(std::tuple<double, Locus*> newGene) {
	this->add(std::get<0>(newGene), std::get<1>(newGene));
	return *this;
}

GenomeTemplate GenomeTemplate::add(
	std::vector<double> genes,
	std::vector<Locus*> loci
) {
	if (genes.size() != loci.size()) throw MismatchedCountsException();

	for (unsigned int i = 0; i < genes.size(); i++)
		this->add(genes[i], loci[i]);
	return *this;
}

GenomeTemplate GenomeTemplate::add(GenomeTemplate other) {
	this->add(other.getGenes());
	return *this;
}

GenomeTemplate GenomeTemplate::add(Gene* newGene) {
	this->genes.push_back(newGene->copy());
	return *this;
}

GenomeTemplate GenomeTemplate::add(std::vector<Gene*> newGenes) {
	for (unsigned int i = 0; i < newGenes.size(); i++)
		this->add(newGenes[i]);
	return *this;
}

GenomeTemplate GenomeTemplate::set(double value, unsigned int index) {
	this->genes[index]->setIndex(value);
	return *this;
}

GenomeTemplate GenomeTemplate::set(Locus * locus, unsigned int index) {
	Gene* gene = locus->getGene(this->genes[index]->getIndex());
	delete(this->genes[index]);
	this->genes[index] = gene;
	return *this;
}

GenomeTemplate GenomeTemplate::set(
	double value,
	Locus * locus,
	unsigned int index
) {
	delete(this->genes[index]);
	this->genes[index] = locus->getGene(value);
	return *this;
}

GenomeTemplate GenomeTemplate::set(Gene* gene, unsigned int index) {
	delete(this->genes[index]);
	this->genes[index] = gene;
	return *this;
}

std::vector<Gene*> GenomeTemplate::getGenes() {
	return this->genes;
}

std::vector<Locus*> GenomeTemplate::getLoci() {
	std::vector<Locus*> loci;
	for (unsigned int i = 0; i < this->genes.size(); i++)
		loci.push_back(this->genes[i]->getLocus());
	return loci;
}

Gene* GenomeTemplate::getGene(unsigned int index) {
	return this->genes[index];
}

Locus* GenomeTemplate::getLocus(unsigned int index) {
	return this->genes[index]->getLocus();
}

unsigned int GenomeTemplate::genomeLength() {
	return this->genes.size();
}
