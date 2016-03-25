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
	T * population;

	LibraryNode();

	public:
	LibraryNode(T * population, int newPopulationSize);

	~LibraryNode();

	T * getIndex(int index);

	//Empty, to maintain compatibility with the GeneNode abstract class
	//(an Individual doesn't care what's going on in here, so this works)
	void setFitnessAtIndex(int index, int newFitness);
	void propagateFitnesses();

	int getFitnessAtIndex(int index);

	virtual std::string toString();
};

