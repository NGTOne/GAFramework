#include "core/Genome.hpp"
#include "core/genes/Gene.t.hpp"
#include "core/FakeGenome.hpp"
#include "core/Locus.hpp"
#include "loci/PopulationLocus.hpp"
#include "loci/FakePopulationLocus.hpp"
#include "exception/ValueOutOfRangeException.hpp"
#include "exception/ComponentNotPresentException.hpp"
#include <cmath>
#include <sstream>

Genome::Genome(std::vector<Locus*> loci, std::string speciesNode) {
	this->speciesNode = speciesNode;
	this->generateRandomGenes(loci);
}

Genome::Genome(
	std::vector<double> genes,
	std::vector<Locus*> loci,
	std::string speciesNode
) {
	std::vector<Gene*> completeGenes;
	for (unsigned int i = 0; i < genes.size(); i++)
		completeGenes.push_back(loci[i]->getGene(genes[i]));
	this->genes = completeGenes;
	this->speciesNode = speciesNode;
}

Genome::Genome(std::vector<Gene*> genes, std::string speciesNode) {
	this->genes = genes;
	this->speciesNode = speciesNode;
}

Genome::Genome(GenomeTemplate geneTemplate, std::string speciesNode) {
	this->setGenes(geneTemplate.getGenes());
	this->speciesNode = speciesNode;
}

Genome::Genome(Genome* other) {
	this->setGenes(other->getGenome());
	this->speciesNode = other->getSpeciesNode();
}

Genome::Genome(Genome* other, bool randomize) {
	this->speciesNode = other->getSpeciesNode();
	if (randomize) {
		this->generateRandomGenes(other->getLoci());
	} else {
		this->setGenes(other->getGenome());
	}
}

Genome::Genome(Genome&& other) {
	this->speciesNode = other.getSpeciesNode();
	this->setGenes(other.getGenome());
}

Genome::Genome(Genome& other) {
	this->speciesNode = other.getSpeciesNode();
	this->setGenes(other.getGenome());
}

Genome::~Genome() {
	for (unsigned int i = 0; i < this->genes.size(); i++)
		delete(this->genes[i]);
}

void Genome::setGenes(std::vector<Gene*> genes) {
	this->genes.clear();
	for (unsigned int i = 0; i < genes.size(); i++)
		this->genes.push_back(genes[i]->copy());
}

void Genome::generateRandomGenes(std::vector<Locus*> loci) {
	this->clearGenome();
	for (unsigned int i = 0; i < loci.size(); i++)
		this->genes.push_back(loci[i]->getGene());
}

void Genome::clearGenome() {
	for (unsigned int i = 0; i < this->genes.size(); i++)
		delete(this->genes[i]);
}

std::vector<Gene*> Genome::getGenome() {
	return this->genes;
}

unsigned int Genome::genomeLength() {
	return this->genes.size();
}

std::vector<Locus*> Genome::getLoci() {
	std::vector<Locus*> loci;
	for (unsigned int i = 0; i < this->genes.size(); i++)
		loci.push_back(this->genes[i]->getLocus());
	return loci;
}

std::string Genome::getSpeciesNode() {
	return this->speciesNode;
}

double Genome::difference(Genome* otherGenome) {
	std::vector<Gene*> otherGenes = otherGenome->getGenome();
	double difference = 0;
	unsigned int shorterGenome = fmin(
		this->genes.size(),
		otherGenes.size()
	);
	unsigned int longerGenome = fmax(
		this->genes.size(),
		otherGenes.size()
	);

	for (unsigned int i = 0; i < shorterGenome; i++)
		difference += std::abs(
			this->genes[i]->getIndex() - otherGenes[i]->getIndex()
		);

	// We want to account for genes of different lengths somehow
	if (longerGenome != shorterGenome)
		difference += longerGenome - shorterGenome;

	return difference;
}

std::string Genome::flatten() {
	std::stringstream ss;

	for (unsigned int i = 0; i < this->genes.size(); i++)
		ss << this->genes[i]->flatten() << " ";

	return ss.str();
}

Genome Genome::flattenGenome(Genome* target, bool exclude) {
	std::vector<Gene*> rawGenome;

	for (unsigned int i = 0; i < this->genomeLength(); i++) {
		Gene* temp = this->genes[i];
		if (!temp->isConstructive()) {
			rawGenome.push_back(temp->copy());
		} else {
			Genome* tempGenome = temp->getValue<Genome*>();

			if (tempGenome == target) {
				if (!exclude) rawGenome.push_back(temp->copy());
			} else {
				Genome flattened = tempGenome->flattenGenome();
				std::vector<Gene*> tempGenes =
					flattened.getGenome();

				for (
					unsigned int k = 0;
					k < tempGenes.size();
					k++
				) rawGenome.push_back(tempGenes[k]->copy());
			}
		}
	}

	return Genome(rawGenome, this->speciesNode);
}

Genome Genome::flattenGenome() {
	return this->flattenGenome(NULL, false);
}

Genome Genome::flattenExceptFor(Genome* target) {
	return this->flattenGenome(target, false);
}

Genome Genome::flattenWithout(Genome* target) {
	return this->flattenGenome(target, true);
}

Genome* Genome::replaceComponent(Genome* target) {
	std::vector<Gene*> newGenes;
	for (unsigned int i = 0; i < this->genes.size(); i++) {
		if (this->genes[i]->isConstructive()) {
			PopulationLocus* temp =
				(PopulationLocus*)this->genes[i]->getLocus();

			if (temp->usesSpecies(target)) {
				newGenes.push_back((new FakePopulationLocus(
					target,
					temp,
					false
				))->getGene());
			} else {
				Genome* replaced = this->getIndex<Genome*>(i)
					->replaceComponent(target);
				newGenes.push_back((new FakePopulationLocus(
					replaced,
					temp,
					true
				))->getGene());
				delete(replaced);
			}
		} else {
			newGenes.push_back(this->genes[i]->copy());
		}
	}
	return new FakeGenome(newGenes, this->speciesNode);
}

std::vector<unsigned int> Genome::getFlattenedIndices(
	Genome* target,
	std::function<bool(Genome*, Genome*)> compare
) {
	std::vector<unsigned int> indices;
	unsigned int currentIndex = 0;

	for (unsigned int i = 0; i < this->genes.size(); i++) {
		if (this->genes[i]->isConstructive()) {
			Genome* temp = this->genes[i]->getValue<Genome*>();
			if (compare(target, temp)) {
				indices.push_back(currentIndex);
			} else {
				std::vector<unsigned int> componentIndices =
					temp->getFlattenedIndices(target);

				for (
					unsigned int k = 0;
					k < componentIndices.size();
					k++
				) {
					indices.push_back(
						componentIndices[k]
							+ currentIndex
					);
				}
			}
			currentIndex += temp->flattenedGenomeLength();
		} else {
			currentIndex++;
		}
	}

	return indices;
}

std::vector<unsigned int> Genome::getFlattenedIndices(Genome* target) {
	return this->getFlattenedIndices(
		target,
		[] (Genome* target, Genome* compare) -> bool {
			return target == compare;
		}
	);
}

std::vector<unsigned int> Genome::getFlattenedSpeciesIndices(Genome* target) {
	return this->getFlattenedIndices(
		target,
		[] (Genome* target, Genome* compare) -> bool {
			return target->getSpeciesNode()
				== compare->getSpeciesNode();
		}
	);
}

unsigned int Genome::flattenedGenomeLength() {
	return this->flattenGenome().genomeLength();
}

bool Genome::isSameSpecies(Genome* target) {
	return this->speciesNode == target->getSpeciesNode();
}

bool Genome::usesComponent(Genome* component) {
	for (unsigned int i = 0; i < this->genes.size(); i++) {
		if (this->genes[i]->isConstructive()) {
			Genome* temp = this->genes[i]->getValue<Genome*>();

			if (
				temp == component
				|| temp->usesComponent(component)
			) return true;
		}
	}

	return false;
}

std::set<Locus*> Genome::getConstructiveLoci() {
	std::set<Locus*> constructiveLoci;
	for (unsigned int i = 0; i < this->genes.size(); i++)
		if (this->genes[i]->isConstructive())
			constructiveLoci.insert(this->genes[i]->getLocus());

	return constructiveLoci;
}

GenomeTemplate Genome::getTemplate() {
	return GenomeTemplate(this->genes);
}
