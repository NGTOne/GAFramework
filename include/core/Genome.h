#pragma once

class Genome {
	private:

	protected:
	int * gene;
	int genomeLength;

	public:
	Genome(int * newGene, int newGenomeLength);

	~Genome();

	int * getGenome();
	int getGenomeLength();
};
