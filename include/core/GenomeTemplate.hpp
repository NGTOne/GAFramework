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

	public:
	GenomeTemplate();
	GenomeTemplate(
		std::vector<unsigned int> genes,
		std::vector<Locus*> loci
	);

	void add(unsigned int gene, Locus * locus);
	void add(std::vector<unsigned int> genes, std::vector<Locus*> loci);

	template<unsigned int i, typename T>
	void updateVector(T newValue);

	std::vector<unsigned int> getGenes();
	std::vector<Locus*> getLoci();
};

template <unsigned int i, typename T>
void GenomeTemplate::updateVector(T newValue) {
	std::vector<T> oldVector = std::get<i>(*this);
	oldVector.push_back(newValue);
	std::get<i>(*this) = oldVector;
}
