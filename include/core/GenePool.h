//This is a base class for both hierarchical and non-hierarchical gene pools
//For hierarchical pools, each individual is an instance of the Individual
//class. For non-hierarchical pools, each "individual" is some literal, for
//instance the letters A-Z or the binary digits 0,1.
//A "standard" GA would be implemented like this:
//HierarchicalPool -> Individual -> (NonHierarchicalPool, NonHierarchicalPool)
#pragma once

class GenePool {
	private:

	protected:
	int populationSize;	
	unsigned seed;

	public:
	virtual void runGenerations()=0;
	void * getIndex(int index);

	GenePool();
	GenePool(unsigned overriddenSeed);

	int getPopulationSize();
	int chooseRandomMember();
	int getSeed();

	bool equals(GenePool * otherPool);
};
