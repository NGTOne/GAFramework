//This class lets us use any objects we might want as properties, whether
//they're basic types or massive structures
class PropertiesList {
	int numProperties;
	void ** properties;

	//Fitness is such a universal example of a property that we detach it
	//from the rest of the list just to make life easy
	int fitness;

	PropertiesList();
	PropertiesList(int newFitness);
	
	~PropertiesList();

	void addProperty(void * newProperty);
	void ** getProperties();
	int getNumProperties();
	int getFitness();
	int setFitness();
};
