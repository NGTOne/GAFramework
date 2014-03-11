//This is a gene pool type that takes basic "literal" types for its genome
//elements - lets us build "classical" GAs
//It has no generational mechanics, selection strategy, or fitness evaluations,
//which means it's distinct from the HierarchicalGenePool

using namespace std;

#include "NonHierarchicalGenePool.h"

NonHierarchicalGenePool::NonHierarchicalGenePool(T population[], int newPopulationSize) {
	myPopulation = population;
	populationSize = newPopulationSize;
	maxValue = sizeof(population)/sizeof(T);
}

void * NonHierarchicalGenePool::getIndex(int index) {
	return (void *)myPopulation[index];
}

//Empty, to maintain compatibility with the GenePool abstract class (an
//Individual doesn't care what's going on in here, so this works)
void NonHierarchicalGenePool::runGenerations() {}
