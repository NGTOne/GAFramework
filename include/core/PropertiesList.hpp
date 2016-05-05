#include "Property.hpp"
#include <vector>
#pragma once

/*
* This class allows the use of any data structure or object type as a
* property - a quantitative measurement of an individual. Using this approach
* gives hierarchical GAs significantly more flexibility.
*/

class PropertiesList {
	private:

	protected:
	std::vector<PropertyBase*> properties;

	// Fitness is such a universal example of a property that we detach it
	// from the rest of the list just to make life easy
	int fitness;

	public:
	PropertiesList();
	PropertiesList(int newFitness);
	
	~PropertiesList();

	void addProperty(PropertyBase * newProperty);
	std::vector<PropertyBase*> getProperties();
	int getNumProperties();
	int getFitness();
	void setFitness(int newFitness);
};
