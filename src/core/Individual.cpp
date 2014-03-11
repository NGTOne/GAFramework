#include "Individual.h"
#include <cstdlib>

using namespace std;

//Basic constructor - lets us have a completely generic Individualthat doesn't
//know what the heck is going on inside it
Individual::Individual(GenePool * newGenePools, CrossoverOperation newCrossover, MutationOperation newMutation, FitnessFunction newFitness) {
	int genomeLength = 0;
		
	if (newGenePools != NULL) {
		genomeLength = sizeof(newGenePools)/sizeof(GenePool);

		if (genomeLength >= 2) {
			myGenePools = newGenePools;
			genome = new int[genomeLength];

			//This way, we don't actually need to know how many
			//genes are in each pool - it can be 2 or 2000
			for (int i = 0; i < genomeLength; i++) {
				genome[i] = myGenePools[i].chooseRandomMember();
			}
		}
	}

	myCrossover = newCrossover;
	myMutation = newMutation;
	myFunction = newFitness;
}

//Constructor that lets us create an Individual with a fully specified genome
//Necessary for crossover/mutation
Individual::Individual(GenePool * newGenePools, CrossoverOperation newCrossover, MutationOperation newMutation, FitnessFunction newFitness, int newGenome[]) {
	int genomeLength = 0;

        if (newGenePools != NULL) {
		genomeLength = sizeof(newGenePools)/sizeof(GenePool);

                if (genomeLength >= 2) {
			myGenePools = newGenePools;
                        genome = new int[genomeLength];

                        //This way, we don't actually need to know how
                        //many genes are in each pool - it can be 2
                        //or 2000
                        for (int i = 0; i < genomeLength; i++) {
				genome[i] = newGenome[i];
                        }
                }
	}

        myCrossover = newCrossover;
        myMutation = newMutation;
        myFunction = newFitness;
}

//Exactly what it says on the tin - wraps around the CrossoverOperation
//and spits out two offspring (which are new instances of Individual)
//Returns NULL if the two parents have different gene pools
Individual * Individual::crossoverOperation(Individual otherParent) {
	int * otherGuysGenome;
	int ** kidsGenome;
	Individual * kids;

	if (sameSpecies(otherParent) == false) {
		return NULL;
	}

	otherGuysGenome = otherParent.getGenome();

	kidsGenome = myCrossover.crossOver(genome, otherGuysGenome);
	
	Individual firstKid(myGenePools, myCrossover, myMutation, myFunction, kidsGenome[0]);
	Individual secondKid(myGenePools, myCrossover, myMutation, myFunction, kidsGenome[1]);
	
	kids[0] = firstKid;
	kids[1] = secondKid;

	return kids;
}

//Wraps around the MutationOperation object and spits out a mutant
//version of this Individual (which is a new instance of Individual)
Individual Individual::mutationOperation() {
	int * mutantGenome;
	int maxValues[genomeLength];

	for (int i = 0; i < genomeLength; i++) {
		maxValues[i] = myGenePools[i].getPopulationSize()-1;
	}

	mutantGenome = myMutation.mutate(genome, maxValues);
	Individual mutant(myGenePools, myCrossover, myMutation, myFunction, mutantGenome);

	return mutant;
}

int Individual::checkFitness() {
	int myFitness;

	myFitness = myFunction.checkFitness(myGenePools, genome, genomeLength);

	return myFitness;
}

//For populating HierarchicalGenePools - basically, use this Individual as a
//template, just generate a new genome for it
Individual Individual::makeRandomCopy() {
	Individual myCopy(myGenePools, myCrossover, myMutation, myFunction);

	return myCopy;
}

//In case we need to copy a given Individual's gene pool/function set, but with
//a new genome
//WARNING - THIS IS VERY DANGEROUS IF DONE MANUALLY
//If the chromosomes in newGenome are out of range for their gene pools, bad
//things will happen
Individual Individual::makeSpecifiedCopy(int newGenome[]) {
	Individual myCopy(myGenePools, myCrossover, myMutation, myFunction, newGenome);

	return myCopy;
}

//Necessary for species verification
GenePool * Individual::getGenePoolList() {
	return myGenePools;
}

//Necessary for crossover
int * Individual::getGenome() {
	return genome;
}

void Individual::runHierarchicalGenerations() {
	for (int i = 0; i < genomeLength; i++) {
		myGenePools[i].runGenerations();
	}
}

//In a hierarchical GA, it's important to know whether or not two individuals
//are from the same part of the hierarchy before attempting to breed them
//Comparing which gene pools they draw from provides an easy way to do this
bool Individual::sameSpecies(Individual otherIndividual) {
	int otherGuysLength = otherIndividual.getGenomeLength();
	GenePool * otherGuysPools = otherIndividual.getGenePoolList();

	//First, a rough check
	if (otherGuysLength != genomeLength) {
		return false;
	}

	//Now, more detailed inspection
	for (int i = 0; i < genomeLength; i++) {
		if (myGenePools[i].equals(otherGuysPools[i]) == false) {
			return false;
		}
	}

	return true;
}

int Individual::getGenomeLength() {

}

string Individual::toString() {
	return myFunction.toString(myGenePools, genome, genomeLength);
}
