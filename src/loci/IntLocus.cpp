#include "loci/IntLocus.hpp"
#include "exception/ValueOutOfRangeException.hpp"
#include <boost/any.hpp>
#include <sstream>

using namespace std;

IntLocus::IntLocus(int bottom, int top) {
	vector<boost::any> newPopulation;

	for (int i = 0; bottom + i <= top; i++)
		newPopulation.push_back(bottom + i);

	Locus::setPopulation(newPopulation);
}

IntLocus::IntLocus(vector<int> values) {
	vector<boost::any> newPopulation;

	for (unsigned int i = 0; i < values.size(); i++)
		newPopulation.push_back(values[i]);

	Locus::setPopulation(newPopulation);
}

int IntLocus::getIndex(unsigned int index) {
	return boost::any_cast<int>(Locus::getIndex(index));
}

IntLocus::~IntLocus() {}

string IntLocus::toString() {
	stringstream ss;

	for (unsigned int i = 0; i < this->population.size(); i++)
		ss << this->getIndex(i) << " ";

	return ss.str();
}

string IntLocus::flatten(unsigned int index) {
	if (this->outOfRange(index)) throw ValueOutOfRangeException();

	stringstream ss;
	ss << this->getIndex(index);
	return ss.str();
}
