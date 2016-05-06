#include "core/PropertiesList.hpp"
#include <cstdlib>

using namespace std;

PropertiesList::PropertiesList() {}

PropertiesList::PropertiesList(int fitness) {
	this->fitness = fitness;
}
	
PropertiesList::~PropertiesList() {
	for (int i = 0; i < properties.size(); i++) {
		delete(properties[i]);
	}
}

void PropertiesList::addProperty(PropertyBase * newProperty) {
	properties.push_back(newProperty);
}

vector<PropertyBase*> PropertiesList::getProperties() {
	return properties;
}

int PropertiesList::getNumProperties() {
	return properties.size();
}

int PropertiesList::getFitness() {
	return fitness;
}

void PropertiesList::setFitness(int newFitness) {
	fitness = newFitness;
}
