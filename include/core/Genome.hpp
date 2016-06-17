#pragma once
#include "Locus.hpp"
#include <vector>
#include <set>
#include <boost/any.hpp>

using namespace std;

class Genome {
	private:

	protected:
	std::vector<unsigned int> genes;
	std::vector<Locus *> loci;

	void generateRandomGenes();
	Genome flattenGenome(Genome * target, bool exclude);

	public:
	Genome(std::vector<Locus *> loci);
	Genome(std::vector<unsigned int> genes, std::vector<Locus *> loci);
	Genome(Genome * other);
	Genome(Genome * other, bool randomize);
	Genome(Genome * other, unsigned int rawGenes[]);

	~Genome();

	std::vector<unsigned int> getGenome();
	unsigned int genomeLength();
	std::vector<Locus *> getLoci();
	int difference(Genome * otherGenome);

	std::string flatten();
	Genome flattenGenome();
	Genome flattenExceptFor(Genome * target);
	Genome flattenWithout(Genome * target);
	unsigned int getFlattenedIndex(Genome * target);

	bool usesComponent(Genome * component);
	set<Locus*> getConstructiveLoci();

	template <typename T>
	bool indexIs(unsigned int index, T target);

	template <typename T>
	T getIndex(unsigned int index);
};

template <typename T>
bool Genome::indexIs(unsigned int index, T target) {
	T value = boost::any_cast<T>(
		this->loci[index]->getIndex(this->genes[index])
	);
	return value == target;
}

template <typename T>
T Genome::getIndex(unsigned int index) {
	return boost::any_cast<T>(
		this->loci[index]->getIndex(this->genes[index])
	);
}
