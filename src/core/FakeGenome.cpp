#include "core/FakeGenome.hpp"
#include "loci/PopulationLocus.hpp"
#include "loci/FakePopulationLocus.hpp"

FakeGenome::FakeGenome(
	std::vector<Gene*> genes,
	std::string speciesNode
) : Genome(genes, speciesNode) {}

FakeGenome::FakeGenome(Genome* other) : Genome(other) {
	for (unsigned int i = 0; i < this->genes.size(); i++)
		if (
			this->genes[i]->isConstructive()
			&& ((PopulationLocus*)this->genes[i]->getLocus())
				->isFake()
		) this->genes[i] = (new FakePopulationLocus(
			(FakePopulationLocus*)this->genes[i]->getLocus()
		))->getGene();
}

FakeGenome::~FakeGenome() {
	for (unsigned int i = 0; i < this->genes.size(); i++)
		if (
			this->genes[i]->isConstructive()
			&& ((PopulationLocus*)this->genes[i]->getLocus())
				->isFake()
		) delete(this->genes[i]->getLocus());
}
