#pragma once
#include "GeneNode.hpp"

/*
* This simple class encapsulates all of an Individual's genetic information,
* including the gene pools it uses, with the goal of easing the sharing of
* this information between classes.
*/

class Genome {
	private:

	protected:
	int * gene;
	int genomeLength;
	GeneNode ** genePools;

	public:
	Genome(int * newGene, int newGenomeLength, GeneNode ** newGeneNodes);

	~Genome();

	int * getGenome();
	int getGenomeLength();
	GeneNode ** getGeneNodes();
	int getDifference(Genome * otherGenome);
};
