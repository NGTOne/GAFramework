#ifndef LOCI_NumericSetLocus
#define LOCI_NumericSetLocus

#include "../core/Locus.hpp"
#include "../core/utils/HierRNG.hpp"
#include "../core/genes/DiscreteGene.hpp"
#include "../core/genes/ContinuousGene.hpp"
#include <limits>
#include <boost/type_index.hpp>
#include <sstream>

template <typename T>
class NumericSetLocus : public Locus {
	static_assert (
		std::is_arithmetic<T>::value,
		"Type provided to NumericSetLocus must be numeric."
	);

	private:

	protected:
	T top;
	T bottom;

	public:
	NumericSetLocus();
	NumericSetLocus(T bottom, T top);

	Gene* getGene();
	Gene* getGene(double index);

	double randomIndex();
	double topIndex();
	double bottomIndex();
	double closestIndex(double index);

	bool outOfRange(double index);

	std::string toString();
	std::string flatten(Gene* index);
	boost::any getIndex(Gene* index);

	using autoGene = typename std::conditional<
		std::is_integral<T>::value,
		DiscreteGene,
		ContinuousGene
	>::type;
};

template <typename T>
NumericSetLocus<T>::NumericSetLocus() {
	this->bottom = std::numeric_limits<T>::lowest();
	this->top = std::numeric_limits<T>::max();
}

template <typename T>
NumericSetLocus<T>::NumericSetLocus(T bottom, T top) {
	this->bottom = bottom;
	this->top = top;
}

template <typename T>
Gene* NumericSetLocus<T>::getGene() {
	return this->getGene(this->randomIndex());
}

template <typename T>
Gene* NumericSetLocus<T>::getGene(double index) {
	return new autoGene(this, this->closestIndex(index));
}

template <typename T>
double NumericSetLocus<T>::randomIndex() {
	return HierRNG::uniform<T>(this->bottomIndex(), this->topIndex());
}

template <typename T>
double NumericSetLocus<T>::topIndex() {
	return this->top;
}

template <typename T>
double NumericSetLocus<T>::bottomIndex() {
	return this->bottom;
}

template <typename T>
double NumericSetLocus<T>::closestIndex(double index) {
	if (index < this->bottomIndex()) return this->bottomIndex();
	if (index > this->topIndex()) return this->topIndex();

	if (std::is_integral<T>::value) return std::round(index);
	return index;
}

template <typename T>
bool NumericSetLocus<T>::outOfRange(double index) {
	return index < this->bottomIndex() || index > this->topIndex();
}

template <typename T>
std::string NumericSetLocus<T>::toString() {
	std::stringstream ss;

	ss << "Numeric set locus using type "
		<< boost::typeindex::type_id<T>().pretty_name()
		<< "and values " << this->bottom
		<< "-" << this->top
		<< " inclusive.\n";
	return ss.str();
}

template <typename T>
std::string NumericSetLocus<T>::flatten(Gene* index) {
	if (Locus::outOfRange(index)) throw ValueOutOfRangeException();

	std::stringstream ss;
	ss << boost::any_cast<T>(this->getIndex(index));
	return ss.str();
}

template <typename T>
boost::any NumericSetLocus<T>::getIndex(Gene* index) {
	if (Locus::outOfRange(index)) throw ValueOutOfRangeException();
	return this->closestIndex(index->getIndex());
}

#endif
