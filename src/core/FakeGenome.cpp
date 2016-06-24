#include "core/FakeGenome.hpp"
#include "loci/PopulationLocus.hpp"

FakeGenome::FakeGenome(
	std::vector<unsigned int> genes,
	std::vector<Locus*> loci,
	std::string speciesNode
) : Genome(genes, loci, speciesNode) {}

FakeGenome::~FakeGenome() {
	for (unsigned int i = 0; i < this->loci.size(); i++)
		if (
			this->loci[i]->isConstructive()
			&& ((PopulationLocus*)this->loci[i])->isFake()
		) delete(this->loci[i]);
}
