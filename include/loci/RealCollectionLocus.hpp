#include "CollectionLocus.hpp"
#include "../core/utils/templates.hpp"
#include "../exception/ValueOutOfRangeException.hpp"
#include <boost/any.hpp>
#include <sstream>
#include <vector>
#include <initializer_list>
#include <string>
#pragma once

template <typename T, typename = EnableIf<std::is_floating_point<T>>>
class RealCollectionLocus: public CollectionLocus {
	private:

	protected:

	public:
	RealCollectionLocus(T bottom, T top, T resolution);
	RealCollectionLocus(std::vector<T> values);
	RealCollectionLocus(std::initializer_list<T> values);

	~RealCollectionLocus();

	std::string toString();
	std::string flatten(Gene* index);
};

template <typename T, class N>
RealCollectionLocus<T, N>::RealCollectionLocus(T bottom, T top, T resolution) {
	std::vector<boost::any> newPopulation;

	for (unsigned int i = 0; bottom + ((T)i * resolution) <= top; i++)
		newPopulation.push_back(bottom + ((T)i * resolution));

	CollectionLocus::setPopulation(newPopulation);
}

template <typename T, class N>
RealCollectionLocus<T, N>::RealCollectionLocus(std::vector<T> values) {
	CollectionLocus::setPopulation(
		std::vector<boost::any>(values.begin(), values.end())
	);
}

template <typename T, class N>
RealCollectionLocus<T, N>::RealCollectionLocus(
	std::initializer_list<T> values
) {
	CollectionLocus::setPopulation(
		std::vector<boost::any>(values.begin(), values.end())
	);
}

template <typename T, class N>
RealCollectionLocus<T, N>::~RealCollectionLocus() {}

template <typename T, class N>
std::string RealCollectionLocus<T, N>::toString() {
	std::stringstream ss;

	for (unsigned int i = 0; i < this->population.size(); i++)
		ss << boost::any_cast<T>(this->getIndex(i)) << " ";

	return ss.str();
}

template <typename T, class N>
std::string RealCollectionLocus<T, N>::flatten(Gene* index) {
	if (this->outOfRange(index)) throw ValueOutOfRangeException();

	std::stringstream ss;
	ss << boost::any_cast<T>(this->getIndex(index));
	return ss.str();
}
