#pragma once
#include "GenePool.hpp"

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
	GenePool ** genePools;

	public:
	Genome(int * newGene, int newGenomeLength, GenePool ** newGenePools);

	~Genome();

	int * getGenome();
	int getGenomeLength();
	GenePool ** getGenePools();
};
