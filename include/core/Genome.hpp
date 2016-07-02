#pragma once
#include "Locus.hpp"
#include "GenomeTemplate.hpp"
#include <vector>
#include <set>
#include <functional>
#include <boost/any.hpp>

using namespace std;

class Genome {
	private:

	protected:
	std::vector<unsigned int> genes;
	std::vector<Locus *> loci;
	std::string speciesNode;

	void generateRandomGenes();
	Genome flattenGenome(Genome * target, bool exclude);

	std::vector<unsigned int> getFlattenedIndices(
		Genome * target,
		std::function<bool(Genome *, Genome *)> compare
	);

	public:
	Genome(std::vector<Locus *> loci, std::string speciesNode);
	Genome(
		std::vector<unsigned int> genes,
		std::vector<Locus *> loci,
		std::string speciesNode
	);
	Genome(GenomeTemplate geneTemplate, std::string speciesNode);
	Genome(Genome * other);
	Genome(Genome * other, bool randomize);
	Genome(Genome * other, unsigned int rawGenes[]);

	virtual ~Genome();

	std::vector<unsigned int> getGenome();
	unsigned int genomeLength();
	unsigned int flattenedGenomeLength();
	std::vector<Locus *> getLoci();
	std::string getSpeciesNode();
	int difference(Genome * otherGenome);

	std::string flatten();
	Genome flattenGenome();
	Genome flattenExceptFor(Genome * target);
	Genome flattenWithout(Genome * target);
	Genome * replaceComponent(Genome * target);
	std::vector<unsigned int> getFlattenedIndices(Genome * target);
	std::vector<unsigned int> getFlattenedSpeciesIndices(Genome * target);

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
