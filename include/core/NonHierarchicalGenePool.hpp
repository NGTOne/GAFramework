#include "GenePool.hpp"
#include <string>
#pragma once

//This is a gene pool type that takes basic "literal" types for its genome
//elements - lets us build "classical" GAs.
//It has no generational mechanics, selection strategy, or fitness evaluations,
//which means it's distinct from the HierarchicalGenePool.
//It is not limited to simple atomic types, either - as a template class, it
//can be used with whatever massive data structures are desired.
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
