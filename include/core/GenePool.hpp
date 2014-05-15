//This is a base class for both hierarchical and non-hierarchical gene pools
//For hierarchical pools, each individual is an instance of the Individual
//class. For non-hierarchical pools, each "individual" is some literal, for
//instance the letters A-Z or the binary digits 0,1.
//A "standard" GA would be implemented like this:
//HierarchicalPool -> Individual -> (NonHierarchicalPool, NonHierarchicalPool)
#pragma once

#include <string>
#include <random>

class GenePool {
	private:

	protected:
	int populationSize;	
	unsigned seed;
	std::mt19937 generator;

	public:
	virtual void runGenerations()=0;
	virtual void * getIndex(int index) = 0;
	virtual void * getFittest() = 0;

	void init(unsigned newSeed);

	GenePool();
	GenePool(unsigned overriddenSeed);

	int getPopulationSize();
	int chooseRandomMember();
	int getSeed();

	virtual int getHighestFitness() = 0;

	bool equals(GenePool * otherPool);

	virtual std::string toString()=0;
};
