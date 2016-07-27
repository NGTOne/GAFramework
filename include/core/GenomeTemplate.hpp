#include "Locus.hpp"
#include "../exception/ValueOutOfRangeException.hpp"
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

	template<unsigned int i, typename T>
	void updateVector(T newValue, unsigned int index);

	public:
	GenomeTemplate();
	GenomeTemplate(
		std::vector<unsigned int> genes,
		std::vector<Locus*> loci
	);

	GenomeTemplate add(unsigned int gene, Locus * locus);
	GenomeTemplate add(std::tuple<unsigned int, Locus*> newGene);
	GenomeTemplate add(
		std::vector<unsigned int> genes,
		std::vector<Locus*> loci
	);
	GenomeTemplate add(GenomeTemplate other);

	GenomeTemplate set(unsigned int value, unsigned int index);
	GenomeTemplate set(Locus* locus, unsigned int index);
	GenomeTemplate set(
		unsigned int value,
		Locus * locus,
		unsigned int index
	);

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

template <unsigned int i, typename T>
void GenomeTemplate::updateVector(T newValue, unsigned int index) {
	std::vector<T> oldVector = std::get<i>(*this);
	if (index >= oldVector.size()) throw ValueOutOfRangeException();
	oldVector[index] = newValue;
	std::get<i>(*this) = oldVector;
}
