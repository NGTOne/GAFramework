#include "Locus.hpp"
#include "genes/Gene.hpp"
#include "../exception/ValueOutOfRangeException.hpp"
#include <vector>
#include <tuple>
#pragma once

class GenomeTemplate {
	private:

	protected:
	std::vector<Gene*> genes;

	public:
	GenomeTemplate();
	GenomeTemplate(
		std::vector<double> genes,
		std::vector<Locus*> loci
	);
	GenomeTemplate(std::vector<Gene*> genes);

	void clearGenes();

	GenomeTemplate add(double gene, Locus* locus);
	GenomeTemplate add(std::tuple<double, Locus*> newGene);
	GenomeTemplate add(
		std::vector<double> genes,
		std::vector<Locus*> loci
	);
	GenomeTemplate add(GenomeTemplate other);
	GenomeTemplate add(Gene* newGene);
	GenomeTemplate add(std::vector<Gene*> newGenes);

	GenomeTemplate set(double value, unsigned int index);
	GenomeTemplate set(Locus* locus, unsigned int index);
	GenomeTemplate set(double value, Locus * locus, unsigned int index);
	GenomeTemplate set(Gene* gene, unsigned int index);

	std::vector<Gene*> getGenes();
	std::vector<Locus*> getLoci();

	Gene* getGene(unsigned int index);
	Locus* getLocus(unsigned int index);

	unsigned int genomeLength();

	static void clearTemplates(std::vector<GenomeTemplate> templates);
};
