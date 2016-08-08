#include "loci/BoolLocus.hpp"
#include "exception/ValueOutOfRangeException.hpp"
#include <boost/any.hpp>
#include <sstream>

BoolLocus::BoolLocus() {
	CollectionLocus::setPopulation({false, true});
}

BoolLocus::~BoolLocus() {}

std::string BoolLocus::toString() {
	std::stringstream ss;

	for (unsigned int i = 0; i < this->population.size(); i++)
		ss << boost::any_cast<bool>(this->getIndex(i)) << " ";

	return ss.str();
}

std::string BoolLocus::flatten(Gene* index) {
	if (this->outOfRange(index)) throw ValueOutOfRangeException();

	std::stringstream ss;
	ss << boost::any_cast<bool>(this->getIndex(index));
	return ss.str();
}
