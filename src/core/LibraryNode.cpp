#include <sstream>
#include <string>
#include "core/LibraryNode.hpp"

using namespace std;

template <class T> LibraryNode<T>::LibraryNode(
	T * population,
	int populationSize
) {
	this->population = population;
	this->populationSize = populationSize;
}

template <class T> LibraryNode<T>::~LibraryNode() {};

template <class T> T * LibraryNode<T>::getIndex(int index) {
	return this->population[index];
}

template <class T> string LibraryNode<T>::toString() {
        string returnString = "";
        stringstream ss;

	for (int i = 0; i < populationSize; i++) {
		ss << population[i].toString() << " ";
	}

	ss << "\nRandom Seed: " << seed << "\n";

        returnString = ss.str();

        return returnString;

}

// Legacy garbage
template <class T> void LibraryNode<T>::setFitnessAtIndex(
	int index,
	int newFitness
) {}
template <class T> void LibraryNode<T>::propagateFitnesses() {}
template <class T> int LibraryNode<T>::getFitnessAtIndex(int index) {}
