#pragma once
#include "Locus.hpp"
#include <vector>

using namespace std;

class Genome {
	private:

	protected:
	std::vector<int> genes;
	std::vector<Locus *> loci;

	void generateRandomGenes();

	public:
	Genome(std::vector<Locus *> loci);
	Genome(std::vector<int> genes, std::vector<Locus *> loci);
	Genome(Genome * other, bool randomize);
	Genome(Genome * other, int rawGenes[]);

	~Genome();

	std::vector<int> getGenome();
	int getGenomeLength();
	std::vector<Locus *> getLoci();
	int getDifference(Genome * otherGenome);
};
