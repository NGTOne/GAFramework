#include "loci/FloatLocus.hpp"
#include "exception/ValueOutOfRangeException.hpp"
#include <boost/any.hpp>
#include <sstream>

using namespace std;

FloatLocus::FloatLocus(float bottom, float top, float resolution) {
	vector<boost::any> newPopulation;

	for (unsigned int i = 0; bottom + ((float)i * resolution) <= top; i++)
		newPopulation.push_back(bottom + (i * resolution));

	Locus::setPopulation(newPopulation);
}

FloatLocus::FloatLocus(vector<float> values) {
	vector<boost::any> newPopulation;

	for (unsigned int i = 0; i < values.size(); i++)
		newPopulation.push_back(values[i]);

	Locus::setPopulation(newPopulation);
}

float FloatLocus::getIndex(unsigned int index) {
	return boost::any_cast<float>(Locus::getIndex(index));
}

FloatLocus::~FloatLocus() {}

string FloatLocus::toString() {
	stringstream ss;

	for (unsigned int i = 0; i < this->population.size(); i++)
		ss << this->getIndex(i) << " ";

	return ss.str();
}

string FloatLocus::flatten(unsigned int index) {
	if (this->outOfRange(index)) throw ValueOutOfRangeException();

	stringstream ss;
	ss << this->getIndex(index);
	return ss.str();
}
