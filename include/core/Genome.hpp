#pragma once
#include "Locus.hpp"
#include <vector>

class Genome {
	private:

	protected:
	std::vector<int> genes;
	std::vector<Locus*> loci;

	public:
	Genome(std::vector<Locus*> loci);
	Genome(std::vector<int> genes, std::vector<Locus*> loci);

	~Genome();

	std::vector<int> getGenome();
	int getGenomeLength();
	std::vector<Locus*> getLoci();
	int getDifference(Genome * otherGenome);
};
