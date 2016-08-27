#include "core/GenomeTemplate.hpp"
#include "exception/MismatchedCountsException.hpp"
#include "core/genes/Gene.t.hpp"

GenomeTemplate::GenomeTemplate() {}

GenomeTemplate::GenomeTemplate(
	std::vector<double> genes,
	std::vector<Locus*> loci
) {
	if (genes.size() != loci.size()) throw MismatchedCountsException();
	for (unsigned int i = 0; i < genes.size(); i++)
		this->genes.push_back(loci[i]->getGene(genes[i]));
}

GenomeTemplate::GenomeTemplate(std::vector<Gene*> genes, bool copy) {
	for (unsigned int i = 0; i < genes.size(); i++)
		this->genes.push_back(copy ? genes[i]->copy() : genes[i]);
}

GenomeTemplate::GenomeTemplate(GenomeTemplate& other) {
	this->addToGenome(other.getGenes());
}

GenomeTemplate::GenomeTemplate(GenomeTemplate&& other) {
	this->genes = other.getGenes();
	other.genes.clear();
}

GenomeTemplate::GenomeTemplate(const GenomeTemplate& other) {
	this->addToGenome(other.genes);
}

GenomeTemplate::GenomeTemplate(const GenomeTemplate&& other) {
	this->addToGenome(other.genes);
}

GenomeTemplate::~GenomeTemplate() {
	this->clearGenes();
}

GenomeTemplate& GenomeTemplate::operator=(GenomeTemplate& other) {
	this->clearGenes();
	this->addToGenome(other.getGenes());
	return *this;
}

GenomeTemplate& GenomeTemplate::operator=(GenomeTemplate&& other) {
	this->clearGenes();
	this->genes = other.getGenes();
	other.genes.clear();
	return *this;
}

GenomeTemplate& GenomeTemplate::operator=(const GenomeTemplate& other) {
	this->clearGenes();
	this->addToGenome(other.genes);
	return *this;
}

GenomeTemplate& GenomeTemplate::operator=(const GenomeTemplate&& other) {
	this->clearGenes();
	this->addToGenome(other.genes);
	return *this;
}

void GenomeTemplate::clearGenes() {
	for (unsigned int i = 0; i < this->genes.size(); i++)
		delete(this->genes[i]);
	this->genes.clear();
}

GenomeTemplate GenomeTemplate::add(double gene, Locus* locus) {
	this->addToGenome(locus->getGene(gene));
	return *this;
}

GenomeTemplate GenomeTemplate::add(std::tuple<double, Locus*> newGene) {
	this->addToGenome(std::get<1>(newGene)->getGene(std::get<0>(newGene)));
	return *this;
}

GenomeTemplate GenomeTemplate::add(
	std::vector<double> genes,
	std::vector<Locus*> loci
) {
	if (genes.size() != loci.size()) throw MismatchedCountsException();

	for (unsigned int i = 0; i < genes.size(); i++)
		this->addToGenome(loci[i]->getGene(genes[i]));
	return *this;
}

GenomeTemplate GenomeTemplate::add(GenomeTemplate other) {
	this->addToGenome(other.getGenes());
	return *this;
}

GenomeTemplate GenomeTemplate::add(Gene* newGene) {
	this->addToGenome(newGene->copy());
	return *this;
}

GenomeTemplate GenomeTemplate::add(std::vector<Gene*> newGenes) {
	for (unsigned int i = 0; i < newGenes.size(); i++)
		this->addToGenome(newGenes[i]->copy());
	return *this;
}

GenomeTemplate GenomeTemplate::set(double value, unsigned int index) {
	this->setGene(this->genes[index]->getLocus()->getGene(value), index);
	return *this;
}

GenomeTemplate GenomeTemplate::set(Locus * locus, unsigned int index) {
	this->setGene(locus->getGene(this->genes[index]->getIndex()), index);
	return *this;
}

GenomeTemplate GenomeTemplate::set(
	double value,
	Locus * locus,
	unsigned int index
) {
	this->setGene(locus->getGene(value), index);
	return *this;
}

GenomeTemplate GenomeTemplate::set(Gene* gene, unsigned int index) {
	this->setGene(gene->copy(), index);
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

void GenomeTemplate::clearTemplates(std::vector<GenomeTemplate> templates) {
	for (unsigned int i = 0; i < templates.size(); i++)
		templates[i].clearGenes();
}

void GenomeTemplate::addToGenome(Gene* gene) {
	this->genes.push_back(gene);
}

void GenomeTemplate::addToGenome(std::vector<Gene*> genes) {
	for (unsigned int i = 0; i < genes.size(); i++)
		this->addToGenome(genes[i]->copy());
}

void GenomeTemplate::setGene(Gene* gene, unsigned int index) {
	delete(this->genes[index]);
	this->genes[index] = gene;
}
