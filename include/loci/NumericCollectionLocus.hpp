#ifndef LOCI_NumericCollectionLocus
#define LOCI_NumericCollectionLocus

#include "CollectionLocus.hpp"
#include "../exception/ValueOutOfRangeException.hpp"
#include <boost/any.hpp>
#include <sstream>
#include <vector>
#include <initializer_list>
#include <string>

template <typename T>
class NumericCollectionLocus: public CollectionLocus {
	static_assert(
		std::is_arithmetic<T>::value,
		"Type provided to NumericCollectionLocus must be numeric."
	);
	private:

	protected:

	public:
	NumericCollectionLocus(T bottom, T top, T interval);
	NumericCollectionLocus(std::vector<T> values);
	NumericCollectionLocus(std::initializer_list<T> values);

	~NumericCollectionLocus();

	std::string toString();
	std::string flatten(Gene* index);
};

template <typename T>
NumericCollectionLocus<T>::NumericCollectionLocus(T bottom, T top, T interval) {
	std::vector<boost::any> newPopulation;

	for (unsigned int i = 0; bottom + ((T)i * interval) <= top; i++)
		newPopulation.push_back(bottom + ((T)i * interval));

	CollectionLocus::setPopulation(newPopulation);
}

template <typename T>
NumericCollectionLocus<T>::NumericCollectionLocus(std::vector<T> values) {
	CollectionLocus::setPopulation(
		std::vector<boost::any>(values.begin(), values.end())
	);
}

template <typename T>
NumericCollectionLocus<T>::NumericCollectionLocus(
	std::initializer_list<T> values
) {
	CollectionLocus::setPopulation(
		std::vector<boost::any>(values.begin(), values.end())
	);
}

template <typename T>
NumericCollectionLocus<T>::~NumericCollectionLocus() {}

template <typename T>
std::string NumericCollectionLocus<T>::toString() {
	std::stringstream ss;

	for (unsigned int i = 0; i < this->population.size(); i++)
		ss << boost::any_cast<T>(this->getIndex(i)) << " ";

	return ss.str();
}

template <typename T>
std::string NumericCollectionLocus<T>::flatten(Gene* index) {
	if (this->outOfRange(index)) throw ValueOutOfRangeException();

	std::stringstream ss;
	ss << boost::any_cast<T>(this->getIndex(index));
	return ss.str();
}

#endif
