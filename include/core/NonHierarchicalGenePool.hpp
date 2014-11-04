#include "GenePool.hpp"
#include <string>
#include <sstream>
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

template <> void * NonHierarchicalGenePool<int>::getIndex(int index);
template <> std::string NonHierarchicalGenePool<int>::toString();

using namespace std;

template <class T> NonHierarchicalGenePool<T>::NonHierarchicalGenePool(T * population, int newPopulationSize) : GenePool() {
	myPopulation = population;
	populationSize = newPopulationSize;
}

template <class T> NonHierarchicalGenePool<T>::~NonHierarchicalGenePool() {

}

template <class T> void * NonHierarchicalGenePool<T>::getIndex(int index) {
	return (void *)myPopulation[index];
}

template <class T> void * NonHierarchicalGenePool<T>::getFittest() {}

template <class T> int NonHierarchicalGenePool<T>::getHighestFitness() {}

template <class T> void NonHierarchicalGenePool<T>::setFitnessAtIndex(int index, int newFitness) {}

template <class T> int NonHierarchicalGenePool<T>::getFitnessAtIndex(int index) {
	return 0;
}

//Empty, to maintain compatibility with the GenePool abstract class (an
//Individual doesn't care what's going on in here, so this works)
template <class T> void NonHierarchicalGenePool<T>::runGenerations() {}
template <class T> void NonHierarchicalGenePool<T>::propagateFitnesses() {}

template <class T> string NonHierarchicalGenePool<T>::toString() {
        string returnString = "";
        stringstream ss;

        for (int i = 0; i < populationSize; i++) {
                ss << myPopulation[i].toString() << " ";
        }

	ss << "\nRandom Seed: " << seed << "\n";

        returnString = ss.str();

        return returnString;

}
