#include "Property.hpp"
#pragma once

//This class lets us use any objects we might want as properties, whether
//they're basic types or massive structures. This approach gives
//hierarchical GAs significantly more flexibility.
class PropertiesList {
	private:
	int numProperties;
	PropertyBase ** properties;

	//Fitness is such a universal example of a property that we detach it
	//from the rest of the list just to make life easy
	int fitness;

	protected:

	public:
	PropertiesList();
	PropertiesList(int newFitness);
	
	~PropertiesList();

	void addProperty(PropertyBase * newProperty);
	PropertyBase ** getProperties();
	int getNumProperties();
	int getFitness();
	void setFitness(int newFitness);
};
