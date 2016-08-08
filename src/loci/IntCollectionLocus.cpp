#include "loci/IntCollectionLocus.hpp"
#include "exception/ValueOutOfRangeException.hpp"
#include <boost/any.hpp>
#include <sstream>

IntCollectionLocus::IntCollectionLocus(int bottom, int top, int interval) {
	std::vector<boost::any> newPopulation;

	for (int i = 0; bottom + interval * i <= top; i++)
		newPopulation.push_back(bottom + interval * i);

	CollectionLocus::setPopulation(newPopulation);
}

IntCollectionLocus::IntCollectionLocus(std::vector<int> values) {
	std::vector<boost::any> newPopulation;

	for (unsigned int i = 0; i < values.size(); i++)
		newPopulation.push_back(values[i]);

	CollectionLocus::setPopulation(newPopulation);
}

IntCollectionLocus::IntCollectionLocus(std::initializer_list<int> values) {
	CollectionLocus::setPopulation(
		std::vector<boost::any>(values.begin(), values.end())
	);
}

IntCollectionLocus::~IntCollectionLocus() {}

std::string IntCollectionLocus::toString() {
	std::stringstream ss;

	for (unsigned int i = 0; i < this->population.size(); i++)
		ss << boost::any_cast<int>(this->getIndex(i)) << " ";

	return ss.str();
}

std::string IntCollectionLocus::flatten(Gene* index) {
	if (this->outOfRange(index)) throw ValueOutOfRangeException();

	std::stringstream ss;
	ss << boost::any_cast<int>(this->getIndex(index));
	return ss.str();
}
