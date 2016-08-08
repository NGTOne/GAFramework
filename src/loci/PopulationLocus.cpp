#include "loci/PopulationLocus.hpp"
#include "exception/ValueOutOfRangeException.hpp"
#include "core/genes/DiscreteGene.hpp"
#include "core/HierRNG.hpp"
#include <boost/any.hpp>
#include <sstream>

PopulationLocus::PopulationLocus(PopulationNode* node) {
	this->node = node;
}

PopulationLocus::~PopulationLocus() {}

Gene* PopulationLocus::getGene() {
	return new DiscreteGene(this, this->randomIndex());
}

Gene* PopulationLocus::getGene(double index) {
	return new DiscreteGene(this, this->closestIndex(index));
}

double PopulationLocus::randomIndex() {
	return HierRNG::uniform<unsigned int>(
		this->bottomIndex(),
		this->topIndex()
	);
}

double PopulationLocus::topIndex() {
	return this->node->populationSize() - 1;
}

double PopulationLocus::bottomIndex() {
	return 0;
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

string PopulationLocus::toString() {
	std::stringstream ss;
	ss << "Locus uses node " << this->nodeName() << "\n";
	return ss.str();
}

string PopulationLocus::nodeName() {
	return this->node->name();
}

string PopulationLocus::flatten(Gene* index) {
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

