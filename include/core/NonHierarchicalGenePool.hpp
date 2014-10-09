#include "GenePool.hpp"
#include <string>
#pragma once

/*
* The NonHierarchicalGenePool class is a template class that allows the
* creation of gene pools of fixed, discrete objects. This allows it to serve
* as a "base case" for hierarchical GAs (the individuals at the bottom of the
* hierarchy draw exclusively from NonHierarchicalGenePools), and as a source
* of genetic information for any GA.
*
* Though it is a subclass of GenePool, it has no generational mechanics,
* selection strategy, or fitness evaluations (those functions are empty,
* to maintain compatibility with the superclass), which means that it is
* entirely passive, doing nothing more than providing information.
*/

template <class T>
class NonHierarchicalGenePool: public GenePool {
	private:

	protected:
	T * myPopulation;

	public:

	NonHierarchicalGenePool(T * population, int newPopulationSize);

	~NonHierarchicalGenePool();

	void * getIndex(int index);
	void * getFittest();

	int getHighestFitness();

	//Empty, to maintain compatibility with the GenePool abstract class
	//(an Individual doesn't care what's going on in here, so this works)
	void runGenerations();
	void setFitnessAtIndex(int index, int newFitness);
	void propagateFitnesses();

	int getFitnessAtIndex(int index);
	
	std::string toString();
};

template <> NonHierarchicalGenePool<int>::NonHierarchicalGenePool(int * population, int newPopulationSize);
template <> void * NonHierarchicalGenePool<int>::getIndex(int index);
