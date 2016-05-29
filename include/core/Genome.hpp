#pragma once
#include "Locus.hpp"
#include <vector>
#include <boost/any.hpp>

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
	int getFlattenedIndex(Genome * target);

	bool usesComponent(Genome * component);

	template <typename T>
	bool indexIs(int index, T target);

	template <typename T>
	T getIndex(int index);
};

template <typename T>
bool Genome::indexIs(int index, T target) {
	T value = boost::any_cast<T>(
		this->loci[index]->getIndex(this->genes[index])
	);
	return value == target;
}

template <typename T>
T Genome::getIndex(int index) {
	return boost::any_cast<T>(this->loci[index]->getIndex(this->genes[index]));
}
