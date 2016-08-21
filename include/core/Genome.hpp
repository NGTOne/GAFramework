#ifndef CORE_GENOME
#define CORE_GENOME

#include "Locus.hpp"
#include "GenomeTemplate.hpp"
#include "genes/Gene.hpp"
#include "genes/Gene.t.hpp"
#include <vector>
#include <set>
#include <functional>
#include <boost/any.hpp>

class Genome {
	private:

	protected:
	std::vector<Gene*> genes;
	std::string speciesNode;

	void setGenes(std::vector<Gene*> genes);
	void generateRandomGenes(std::vector<Locus*> loci);
	void clearGenome();
	Genome flattenGenome(Genome* target, bool exclude);

	std::vector<unsigned int> getFlattenedIndices(
		Genome* target,
		std::function<bool(Genome*, Genome*)> compare
	);

	public:
	Genome(std::vector<Locus*> loci, std::string speciesNode);
	Genome(
		std::vector<double> genes,
		std::vector<Locus*> loci,
		std::string speciesNode
	);
	Genome(std::vector<Gene*> genes, std::string speciesNode);
	Genome(GenomeTemplate geneTemplate, std::string speciesNode);
	Genome(Genome* other);
	Genome(Genome* other, bool randomize);
	Genome(Genome&& other);
	Genome(Genome& other);

	virtual ~Genome();

	std::vector<Gene*> getGenome();
	std::vector<Locus*> getLoci();
	unsigned int genomeLength();
	unsigned int flattenedGenomeLength();
	std::string getSpeciesNode();
	double difference(Genome* otherGenome);

	std::string flatten();
	Genome flattenGenome();
	Genome flattenExceptFor(Genome* target);
	Genome flattenWithout(Genome* target);
	Genome * replaceComponent(Genome* target);
	std::vector<unsigned int> getFlattenedIndices(Genome* target);
	std::vector<unsigned int> getFlattenedSpeciesIndices(Genome* target);

	bool isSameSpecies(Genome* other);
	bool usesComponent(Genome* component);
	std::set<Locus*> getConstructiveLoci();
	GenomeTemplate getTemplate();

	template <typename T>
	bool indexIs(unsigned int index, T target);

	template <typename T>
	T getIndex(unsigned int index);
};

template <typename T>
bool Genome::indexIs(unsigned int index, T target) {
	return this->genes[index]->getValue<T>() == target;
}

template <typename T>
T Genome::getIndex(unsigned int index) {
	return this->genes[index]->getValue<T>();
}

#endif
