#include <propagators/DownPropagator.hpp>

void DownPropagator::propagateFitnesses(Individual ** population, int populationSize) {
	int tempFitness;
	Genome * tempGenome;
	GenePool ** tempPools;
	int tempGenomeLength;

	for (int i = 0; i < populationSize; i++) {
		tempFitness = population[i]->getFitness();
		
		tempGenome = population[i]->getGenome();
		tempPools = tempGenome->getGenePools();
		tempGenomeLength = tempGenome->getGenomeLength();
		
		for (int k = 0; k < tempGenomeLength; k++) {
			if (tempPools[k]->getFitnessAtIndex(i) < population[i]->getFitness()) {
				tempPools[k]->setFitnessAtIndex(i, population[i]->getFitness());
			}

			tempPools[k]->propagateFitnesses();
		}
	}
}
