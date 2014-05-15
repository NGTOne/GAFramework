#include "FitnessMatchEnd.hpp"

FitnessMatchEnd::FitnessMatchEnd(int newMinimumFitness) {
	minimumFitness = newMinimumFitness;
}

bool FitnessMatchEnd::checkCondition(Individual * individualToCheck) {
	int * individualsProperties = individualToCheck->getProperties();
	int individualsFitness = individualsProperties[1];

	if (individualsFitness >= minimumFitness) {
		return true;
	} else {
		return false;
	}
}
