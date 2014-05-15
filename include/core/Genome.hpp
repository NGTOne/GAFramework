#pragma once
#include "GenePool.hpp"

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
