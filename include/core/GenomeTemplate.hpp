#include "Locus.hpp"
#include <vector>
#include <tuple>
#pragma once

class GenomeTemplate: public std::tuple<
	std::vector<unsigned int>,
	std::vector<Locus*>
> {
	private:

	protected:
	template<unsigned int i, typename T>
	void updateVector(T newValue);

	public:
	GenomeTemplate();
	GenomeTemplate(
		std::vector<unsigned int> genes,
		std::vector<Locus*> loci
	);

	void add(unsigned int gene, Locus * locus);
	void add(std::tuple<unsigned int, Locus*> newGene);
	void add(std::vector<unsigned int> genes, std::vector<Locus*> loci);
	void add(GenomeTemplate other);

	std::vector<unsigned int> getGenes();
	std::vector<Locus*> getLoci();

	unsigned int getGene(unsigned int index);
	Locus * getLocus(unsigned int index);
	std::tuple<unsigned int, Locus*> getIndex(unsigned int index);

	unsigned int genomeLength();
};

template <unsigned int i, typename T>
void GenomeTemplate::updateVector(T newValue) {
	std::vector<T> oldVector = std::get<i>(*this);
	oldVector.push_back(newValue);
	std::get<i>(*this) = oldVector;
}
