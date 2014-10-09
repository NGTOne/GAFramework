#pragma once

#include <string>
#include <random>

/*
* This class allows us to create pools of genetic information that can be
* recombined. GenePool itself is an abstract class, and is NEVER meant to be
* implemented or used by itself. By extending GenePool, we can create
* different types of gene pools, for vastly different types of genetic
* information.
*/

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
	virtual void setFitnessAtIndex(int index, int newFitness) = 0;

	virtual int getFitnessAtIndex(int index) = 0;

	virtual void propagateFitnesses() = 0;

	GenePool();
	GenePool(unsigned overriddenSeed);

	int getPopulationSize();
	int chooseRandomMember();
	int getSeed();

	virtual int getHighestFitness() = 0;

	bool equals(GenePool * otherPool);

	virtual std::string toString()=0;
};
