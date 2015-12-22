#include <propagators/DownPropagator.hpp>

void DownPropagator::propagateFitnesses(Individual ** population, int populationSize) {
	int tempFitness;
	Genome * tempGenome;
	GeneNode ** tempPools;
	int tempGenomeLength;
	int * tempIndexes;

	for (int i = 0; i < populationSize; i++) {
		tempFitness = population[i]->getFitness();
		
		tempGenome = population[i]->getGenome();
		tempPools = tempGenome->getGeneNodes();
		tempGenomeLength = tempGenome->getGenomeLength();
		tempIndexes = tempGenome->getGenome();		

		for (int k = 0; k < tempGenomeLength; k++) {
			if (tempPools[k]->getFitnessAtIndex(tempIndexes[k]) < tempFitness) {
				tempPools[k]->setFitnessAtIndex(tempIndexes[k], tempFitness);
			}

			//TODO: Find a more efficient (read: not n^2) way to do
			//this
			tempPools[k]->propagateFitnesses();
		}
	}
}
