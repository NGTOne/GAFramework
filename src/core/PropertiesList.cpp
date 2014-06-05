#include "core/PropertiesList.hpp"
#include <cstdlib>

using namespace std;

PropertiesList::PropertiesList() {
	numProperties = 0;
	properties = NULL;
	fitness = 0;
}

PropertiesList::PropertiesList(int newFitness) {
	numProperties = 0;
	properties = NULL;
	fitness = newFitness;
}
	
PropertiesList::~PropertiesList() {
	if (properties != NULL) {
		for (int i = 0; i < numProperties; i++) {
			delete(properties[i]);
		}

		free(properties);
	}
}

void PropertiesList::addProperty(PropertyBase * newProperty) {
	properties = (PropertyBase**)realloc(properties, sizeof(PropertyBase*)*(numProperties+1));
	properties[numProperties] = newProperty;
	numProperties += 1;
}

PropertyBase ** PropertiesList::getProperties() {
	return properties;
}

int PropertiesList::getNumProperties() {
	return numProperties;
}

int PropertiesList::getFitness() {
	return fitness;
}

void PropertiesList::setFitness(int newFitness) {
	fitness = newFitness;
}
