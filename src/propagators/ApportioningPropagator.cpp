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
	GeneNode ** pools;
	int genomeLength;
	int * indexes;

	int * numUses = (int*)malloc(sizeof(int)*populationSize);

	for (i = 0; i < populationSize; i++) {
		numUses[i] = 0;
		genome = population[i]->getGenome();
		pools = genome->getGeneNodes();
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

void ApportioningPropagator::propagateFitnesses(Individual ** population, int populationSize) {
	int fitnessContribution, assignableFitness;
	int i, k, c;
	Genome * genome;
	GeneNode ** pools;
	int genomeLength, *indexes;
	Individual * temp;
	Individual ** used = (Individual**)malloc(sizeof(Individual*));
	int numUsed = 1;
	bool componentUsed;
	int fitness;

	for (i = 0; i < populationSize; i++) {
		genome = population[i]->getGenome();
		genomeLength = genome->getGenomeLength();
		pools = genome->getGeneNodes();
		indexes = genome->getGenome();

		for (k = 0; k < genomeLength; k++) {
			temp = (Individual*)pools[k]->getIndex(indexes[i]);
			componentUsed = false;

			for (c = 0; c < numUsed; c++) if (temp == used[c]) componentUsed = true;
			if (!used) {
				used[numUsed-1] = temp;
				used = (Individual**)realloc(used, sizeof(Individual*) * ++numUsed);
			}
		}
	}

	for (i = 0; i < numUsed; i++) {
		fitness = this->getAssignableFitness(population, populationSize, used[i]);
		used[i]->setFitness(fitness);
	}

	for (i = 0; i < populationSize; i++) {
		genome = population[i]->getGenome();
		genomeLength = genome->getGenomeLength();
		pools = genome->getGeneNodes();

		for (k = 0; k < genomeLength; k++) {
			pools[k]->propagateFitnesses();	
		}
	}
}

int ApportioningPropagator::getFitnessValue(Individual * user, Individual * used) {
	if (user->usesComponent(used)) {
		return this->getFitnessContribution(user, used);
	} else {
		return 0;
	}
}
