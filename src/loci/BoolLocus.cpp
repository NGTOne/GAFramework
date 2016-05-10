#include "loci/BoolLocus.hpp"
#include "exception/ValueOutOfRangeException.hpp"
#include <boost/any.hpp>
#include <sstream>

using namespace std;

BoolLocus::BoolLocus() {
	vector<boost::any> newPopulation;
	newPopulation.push_back(false);
	newPopulation.push_back(true);

	Locus::setPopulation(newPopulation);
}

bool BoolLocus::getIndex(int index) {
	return boost::any_cast<bool>(Locus::getIndex(index));
}

BoolLocus::~BoolLocus() {}

string BoolLocus::toString() {
	stringstream ss;

	for (int i = 0; i < population.size(); i++) {
		ss << this->getIndex(i) << " ";
	}

	ss << "\nRandom Seed: " << seed << "\n";

	return ss.str();
}

string BoolLocus::flatten(int index) {
	if (outOfRange(index)) throw ValueOutOfRangeException();

	stringstream ss;
	ss << this->getIndex(index);
	return ss.str();
}
