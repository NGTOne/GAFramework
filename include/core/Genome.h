#pragma once
#include "GenePool.h"

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
