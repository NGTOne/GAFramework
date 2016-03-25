#include "GeneNode.hpp"
#include <string>
#include <sstream>
#pragma once

/*
* The LibraryNode class is a template class that allows the
* creation of gene pools of fixed, discrete objects. This allows it to serve
* as a "base case" for hierarchical GAs (the individuals at the bottom of the
* hierarchy draw exclusively from LibraryNodes), and as a source
* of genetic information for any GA.
*
* Though it is a subclass of GeneNode, it has no generational mechanics,
* selection strategy, or fitness evaluations (those functions are empty,
* to maintain compatibility with the superclass), which means that it is
* entirely passive, doing nothing more than providing information.
*/

template <class T>
class LibraryNode: public GeneNode {
	private:

	protected:
	T * myPopulation;

	public:

	LibraryNode(T * population, int newPopulationSize);

	~LibraryNode();

	void * getIndex(int index);

	int getHighestFitness();

	//Empty, to maintain compatibility with the GeneNode abstract class
	//(an Individual doesn't care what's going on in here, so this works)
	void runGenerations();
	void setFitnessAtIndex(int index, int newFitness);
	void propagateFitnesses();

	int getFitnessAtIndex(int index);

	std::string toString();
};

//Since primitive types behave a bit differently, we need special versions
//of these functions for them
template <> void * LibraryNode<int>::getIndex(int index);
template <> std::string LibraryNode<int>::toString();

template <> void * LibraryNode<double>::getIndex(int index);
template <> std::string LibraryNode<double>::toString();

template <> void * LibraryNode<char>::getIndex(int index);
template <> std::string LibraryNode<char>::toString();

template <> void * LibraryNode<bool>::getIndex(int index);
template <> std::string LibraryNode<bool>::toString();

template <> void * LibraryNode<std::string>::getIndex(int index);
template <> std::string LibraryNode<std::string>::toString();

using namespace std;

template <class T> LibraryNode<T>::LibraryNode(
	T * population,
	int newPopulationSize
) : GeneNode() {
	myPopulation = population;
	populationSize = newPopulationSize;
}

template <class T> LibraryNode<T>::~LibraryNode() {

}

template <class T> void * LibraryNode<T>::getIndex(int index) {
	return (void *)myPopulation[index];
}

template <class T> int LibraryNode<T>::getHighestFitness() {}

template <class T> void LibraryNode<T>::setFitnessAtIndex(
	int index,
	int newFitness
) {}

template <class T> int LibraryNode<T>::getFitnessAtIndex(int index) {
	return 0;
}

//Empty, to maintain compatibility with the GeneNode abstract class (an
//Individual doesn't care what's going on in here, so this works)
template <class T> void LibraryNode<T>::runGenerations() {}
template <class T> void LibraryNode<T>::propagateFitnesses() {}

template <class T> string LibraryNode<T>::toString() {
        string returnString = "";
        stringstream ss;

	for (int i = 0; i < populationSize; i++) {
		ss << myPopulation[i].toString() << " ";
	}

	ss << "\nRandom Seed: " << seed << "\n";

        returnString = ss.str();

        return returnString;

}
