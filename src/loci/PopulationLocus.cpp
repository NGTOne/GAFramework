#include "loci/PopulationLocus.hpp"
#include "exception/ValueOutOfRangeException.hpp"
#include "core/genes/DiscreteGene.hpp"
#include "core/utils/HierRNG.hpp"
#include <boost/any.hpp>
#include <sstream>
#include <algorithm>

PopulationLocus::PopulationLocus(PopulationNode* node) {
	std::vector<unsigned int> validIndices(node->populationSize());
	std::iota(validIndices.begin(), validIndices.end(), 0);
	this->init(node, validIndices);
}

PopulationLocus::PopulationLocus(
	PopulationNode* node,
	unsigned int bottomIndex,
	unsigned int topIndex
) {
	if (topIndex >= node->populationSize())
		throw ValueOutOfRangeException("Top index value cannot be greater than the population size!");
	std::vector<unsigned int> validIndices(topIndex-bottomIndex);
	std::iota(validIndices.begin(), validIndices.end(), bottomIndex);
	this->init(node, validIndices);
}

PopulationLocus::~PopulationLocus() {}

void PopulationLocus::init(
	PopulationNode* node,
	std::vector<unsigned int> validIndices
) {
	this->node = node;
	this->validIndices = validIndices;
}

Gene* PopulationLocus::getGene() {
	return new DiscreteGene(this, this->randomIndex());
}

Gene* PopulationLocus::getGene(double index) {
	return new DiscreteGene(this, this->closestIndex(index));
}

double PopulationLocus::randomIndex() {
	return HierRNG::uniform(this->validIndices);
}

double PopulationLocus::topIndex() {
	return (*this->validIndices.end())-1;
}

double PopulationLocus::bottomIndex() {
	return (*this->validIndices.begin());
}

double PopulationLocus::closestIndex(double index) {
	if (index < this->bottomIndex()) return this->bottomIndex();
	if (index > this->topIndex()) return this->topIndex();
	return std::round(index);
}

bool PopulationLocus::outOfRange(double index) {
	return index < this->bottomIndex() || index > this->topIndex();
}

bool PopulationLocus::outOfRange(Gene* index) {
	return this->outOfRange(index->getIndex());
}

bool PopulationLocus::isConstructive() {
	return true;
}

bool PopulationLocus::isFake() {
	return false;
}

bool PopulationLocus::usesSpecies(Genome* target) {
	return this->node->name() == target->getSpeciesNode();
}

std::string PopulationLocus::toString() {
	std::stringstream ss;
	ss << "Locus uses node " << this->nodeName() << "\n";
	return ss.str();
}

std::string PopulationLocus::nodeName() {
	return this->node->name();
}

std::string PopulationLocus::flatten(Gene* index) {
	if (this->outOfRange(index)) throw ValueOutOfRangeException();

	std::stringstream ss;
	ss << boost::any_cast<Genome*>(this->getIndex(index))->flatten();
	return ss.str();
}

boost::any PopulationLocus::getIndex(Gene* index) {
	return this->node->getIndex(this->closestIndex(index->getIndex()));
}

PopulationNode * PopulationLocus::getNode() {
	return this->node;
}
