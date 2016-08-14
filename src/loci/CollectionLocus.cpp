#include "loci/CollectionLocus.hpp"
#include "core/genes/DiscreteGene.hpp"
#include "core/utils/HierRNG.hpp"
#include "exception/ValueOutOfRangeException.hpp"

CollectionLocus::CollectionLocus() {}

CollectionLocus::CollectionLocus(std::vector<boost::any> population) {
	this->population = population;
}

CollectionLocus::~CollectionLocus() {}

void CollectionLocus::setPopulation(std::vector<boost::any> population) {
	this->population = population;
}

boost::any CollectionLocus::getIndex(double index) {
	if (this->outOfRange(index)) throw ValueOutOfRangeException();
	return this->population[(unsigned int)this->closestIndex(index)];
}

Gene* CollectionLocus::getGene() {
	return this->getGene(this->randomIndex());
}

Gene* CollectionLocus::getGene(double index) {
	return new DiscreteGene(this, this->closestIndex(index));
}

double CollectionLocus::randomIndex() {
	return HierRNG::uniform<unsigned int>(
		this->bottomIndex(),
		this->topIndex()
	);
}

double CollectionLocus::topIndex() {
	return this->population.size() - 1;
}

double CollectionLocus::bottomIndex() {
	return 0;
}

double CollectionLocus::closestIndex(double index) {
	if (index < this->bottomIndex()) return this->bottomIndex();
	if (index > this->topIndex()) return this->topIndex();
	return std::round(index);
}

bool CollectionLocus::outOfRange(double index) {
	return index < this->bottomIndex() || index > this->topIndex();
}

bool CollectionLocus::outOfRange(Gene* index) {
	return this->outOfRange(index->getIndex());
}

boost::any CollectionLocus::getIndex(Gene* index) {
	return this->getIndex(index->getIndex());
}
