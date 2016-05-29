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
	Genome flattenGenome(Genome * target, bool exclude);

	public:
	Genome(std::vector<Locus *> loci);
	Genome(std::vector<int> genes, std::vector<Locus *> loci);
	Genome(Genome * other);
	Genome(Genome * other, bool randomize);
	Genome(Genome * other, int rawGenes[]);

	~Genome();

	std::vector<int> getGenome();
	int genomeLength();
	std::vector<Locus *> getLoci();
	int difference(Genome * otherGenome);

	std::string flatten();
	Genome flattenGenome();
	Genome flattenExceptFor(Genome * target);
	Genome flattenWithout(Genome * target);

	bool usesComponent(Genome * component);
};
