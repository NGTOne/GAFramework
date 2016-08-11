#include "core/FakeGenome.hpp"
#include "loci/PopulationLocus.hpp"
#include "loci/FakePopulationLocus.hpp"

FakeGenome::FakeGenome(
	std::vector<Gene*> genes,
	std::string speciesNode
) : Genome(genes, speciesNode) {}

FakeGenome::FakeGenome(Genome* other) : Genome(other) {
	for (unsigned int i = 0; i < this->genes.size(); i++) {
		Gene* temp = this->genes[i];
		if (
			temp->isConstructive()
			&& ((PopulationLocus*)temp->getLocus())->isFake()
		) {
			this->genes[i] = (new FakePopulationLocus(
				(FakePopulationLocus*)temp->getLocus()
			))->getGene();
			delete(temp);
		}
	}
}

FakeGenome::~FakeGenome() {
	for (unsigned int i = 0; i < this->genes.size(); i++)
		if (
			this->genes[i]->isConstructive()
			&& ((PopulationLocus*)this->genes[i]->getLocus())
				->isFake()
		) delete(this->genes[i]->getLocus());
}
