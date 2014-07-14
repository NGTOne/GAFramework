#pragma once
#include "GenePool.hpp"

//This simple class allows for encapsulation of an individual's genetic
//information, and for keeping the genome and its gene pools together.
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
