//This is a gene pool type that takes basic "literal" types for its genome
//elements - lets us build "classical" GAs
//It has no generational mechanics, selection strategy, or fitness evaluations,
//which means it's distinct from the HierarchicalGenePool
#include "GenePool.h"
#include <string>
#pragma once

template <class T>
class NonHierarchicalGenePool: public GenePool {
	private:

	protected:
	T * myPopulation;

	public:

	NonHierarchicalGenePool();	
	NonHierarchicalGenePool(T * population, int newPopulationSize);

	void * getIndex(int index);

	//Empty, to maintain compatibility with the GenePool abstract class
	//(an Individual doesn't care what's going on in here, so this works)
	void runGenerations();
	
	std::string toString();
};

template <> NonHierarchicalGenePool<int>::NonHierarchicalGenePool(int * population, int newPopulationSize);
template <> void * NonHierarchicalGenePool<int>::getIndex(int index);
