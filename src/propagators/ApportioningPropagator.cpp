#include <propagators/ApportioningPropagator.hpp>

int ApportioningPropagator::getIndividualCount(Individual ** population, int populationSize, Individual * target) {
	int numUses=0, i, *useCounts;
	useCounts = this->getUseCount(population, populationSize, target);

	for (i = 0; i < populationSize; i++) if (useCounts[i] > 0) numUses++;
	free(useCounts);

	return numUses;
}

int * ApportioningPropagator::getUseCount(Individual ** population, int populationSize, Individual * target) {
	int i, k;
	Genome * genome;
	GenePool ** pools;
	int genomeLength;
	int * indexes;

	int * numUses = (int*)malloc(sizeof(int)*populationSize);

	for (i = 0; i < populationSize; i++) {
		numUses[i] = 0;
		genome = population[i]->getGenome();
		pools = genome->getGenePools();
		genomeLength = genome->getGenomeLength();
		indexes = genome->getGenome();

		for (k = 0; k < genomeLength; k++) {
			if (target == (Individual*)pools[k]->getIndex(indexes[k])) {
				numUses[i]++;
			}
		}
	}

	return numUses;
}
