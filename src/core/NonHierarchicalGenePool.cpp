//This is a gene pool type that takes basic "literal" types for its genome
//elements - lets us build "classical" GAs
//It has no generational mechanics, selection strategy, or fitness evaluations,
//which means it's distinct from the HierarchicalGenePool

using namespace std;

#include "NonHierarchicalGenePool.h"

template <class T> NonHierarchicalGenePool<T>::NonHierarchicalGenePool(T population[], int newPopulationSize) {
	myPopulation = population;
	populationSize = newPopulationSize;
}

template <class T> void * NonHierarchicalGenePool<T>::getIndex(int index) {
	return (void *)myPopulation[index];
}

//Empty, to maintain compatibility with the GenePool abstract class (an
//Individual doesn't care what's going on in here, so this works)
template <class T> void NonHierarchicalGenePool<T>::runGenerations() {}
