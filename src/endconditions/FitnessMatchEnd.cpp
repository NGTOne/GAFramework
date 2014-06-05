#include "endconditions/FitnessMatchEnd.hpp"

FitnessMatchEnd::FitnessMatchEnd(int newMinimumFitness) {
	minimumFitness = newMinimumFitness;
}

bool FitnessMatchEnd::checkCondition(Individual * individualToCheck) {
	PropertiesList * properties = individualToCheck->getProperties();
	int individualsFitness = properties->getFitness();

	if (individualsFitness >= minimumFitness) {
		return true;
	} else {
		return false;
	}
}
