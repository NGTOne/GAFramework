#pragma once

#include <string>
#include <random>

/*
* This class allows us to create pools of genetic information that can be
* recombined. GeneNode itself is an abstract class, and is NEVER meant to be
* implemented or used by itself. By extending GeneNode, we can create
* different types of gene pools, for vastly different types of genetic
* information.
*/

class GeneNode {
	private:

	protected:
	int populationSize;	
	unsigned seed;
	std::mt19937 generator;

	public:
	virtual ~GeneNode()=0;

	virtual void runGenerations()=0;
	virtual void * getIndex(int index) = 0;

	void init(unsigned newSeed);
	virtual void setFitnessAtIndex(int index, int newFitness) = 0;

	virtual int getFitnessAtIndex(int index) = 0;

	virtual void propagateFitnesses() = 0;

	GeneNode();
	GeneNode(unsigned overriddenSeed);

	int getPopulationSize();
	int chooseRandomMember();
	int getSeed();

	virtual int getHighestFitness() = 0;

	bool equals(GeneNode * otherPool);

	virtual std::string toString()=0;
};
