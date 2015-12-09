#include "endconditions/FitnessMatchEnd.hpp"

FitnessMatchEnd::FitnessMatchEnd(int newMinimumFitness) {
	minimumFitness = newMinimumFitness;
}

bool FitnessMatchEnd::checkIndividual(Individual * target) {
	PropertiesList * properties = target->getProperties();
	int individualsFitness = properties->getFitness();

	return properties->getFitness() >= minimumFitness ? true : false;
}

bool FitnessMatchEnd::checkCondition(Individual ** population, int populationSize) {
	for (int i = 0; i < populationSize; i++) {
		if (checkIndividual(population[i])) return true;
	}
	return false;
}
