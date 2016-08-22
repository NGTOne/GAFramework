#include <sstream>
#include <string>
#include <libHierGA/HierGA.hpp>
#include "SphereFitness.hpp"
#include <math.h>

using namespace std;

SphereFitness::SphereFitness() : ObjectiveFunction() {}

float SphereFitness::checkFitness(Genome * genome) {
	double total = 0;
	Genome flattened = genome->flattenGenome();

	for (unsigned int i = 0; i < 32; i++)
		total += pow(flattened.getIndex<double>(i), 2);

	return -total;
}

string SphereToString::toString(Genome * genome) {
	stringstream ss;
	Genome flattened = genome->flattenGenome();
	
	for (unsigned int i = 0; i < 32; i++)
		ss << flattened.getIndex<double>(i) << " ";
		
	return ss.str();
}
