//This is a gene pool type that takes basic "literal" types for its genome
//elements - lets us build "classical" GAs
//It has no generational mechanics, selection strategy, or fitness evaluations,
//which means it's distinct from the HierarchicalGenePool

using namespace std;

#include <sstream>
#include <string>
#include "NonHierarchicalGenePool.h"

//EMPTY CONSTRUCTOR, DO NOT USE EVER
template <class T> NonHierarchicalGenePool<T>::NonHierarchicalGenePool() : GenePool() {}

template <class T> NonHierarchicalGenePool<T>::NonHierarchicalGenePool(T * population, int newPopulationSize) : GenePool() {
	myPopulation = population;
	populationSize = newPopulationSize;
}

template <> NonHierarchicalGenePool<int>::NonHierarchicalGenePool(int * population, int newPopulationSize) : GenePool() {
	myPopulation = population;
	populationSize = newPopulationSize;
}

template <class T> void * NonHierarchicalGenePool<T>::getIndex(int index) {
	return (void *)myPopulation[index];
}

template <> void * NonHierarchicalGenePool<int>::getIndex(int index) {
	int * returnValue = &myPopulation[index];

	return (void*)returnValue;
}

//Empty, to maintain compatibility with the GenePool abstract class (an
//Individual doesn't care what's going on in here, so this works)
template <class T> void NonHierarchicalGenePool<T>::runGenerations() {}

template <class T> string NonHierarchicalGenePool<T>::toString() {
        string returnString = "";
        stringstream ss;

        for (int i = 0; i < populationSize; i++) {
                ss << myPopulation[i].toString() << " ";
        }

        returnString = ss.str();

        return returnString;

}

template <> string NonHierarchicalGenePool<int>::toString() {
	string returnString = "";
	stringstream ss;

	for (int i = 0; i < populationSize; i++) {
		ss << myPopulation[i] << " ";
	}

	returnString = ss.str();

	return returnString;
}
