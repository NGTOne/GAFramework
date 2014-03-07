#include <cstdlib>

class Individual {
	private:

	protected:
	int genomeLength;

	//The genome is represented as a series of integers which refer to
	//specific individuals in each gene pool - this frees the individual
	// from reliance on a specific gene type, and lets us mix hierarchical
	//and non-hierarchical genes freely by varying which gene pools it
	// draws from
	int * genome;

	//A gene pool is a collection of any elements that can be used as genome
	//components - for instance, it can be the English alphabet, a set
	//of digits, or a population of individuals for a hierarchical GA
	GenePool myGenePools[];

	CrossoverOperation myCrossover;
	MutationOperation myMutation;
	FitnessFunction myFunction;

	public:
	Individual[] crossoverOperation(Individual otherParent);
	Individual mutationOperation();
	int checkFitness();
	boolean sameSpecies (Individual otherIndividual);
	Individual makeRandomCopy();
	GenePool[] getGenePoolList();
        int[] getGenome();

	//Basic constructor - lets us have a completely generic Individual
	//that doesn't know what the heck is going on inside it
	Individual(GenePool[] newGenePools, CrossoverOperation newCrossover, MutationOperation newMutation, FitnessFunction newFitness) {
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
					genome[i] = myGenePools[i].chooseRandomMember();
				}
			}
		}

		myCrossover = newCrossover;
		myMutation = newMutation;
		myFunction = newFitness;
	}

	//Constructor that lets us create an Individual with a fully specified
	//genome - necessary for crossover/mutation
	Individual(GenePool[] newGenePools, CrossoverOperation newCrossover, MutationOperation newMutation, FitnessFunction newFitness, int[] newGenome) {
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
	Individual[] crossoverOperation(Individual otherParent) {
		int otherGuysGenome[];
		int kidsGenome[][];
		Individual[2] kids;

		if (sameSpecies(otherIndividual) == false) {
			return NULL;
		}

		otherGuysGenome = otherParent.getGenome();

		kidsGenome = myCrossover.crossOver(genome, otherGuysGenome);
		kids[0] = new Individual(myGenePools, myCrossover, myMutation, myFunction, kidsGenome[0]);
		kids[1] = new Individual(myGenePools, myCrossover, myMutation, myFunction, kidsGenome[1]);
		return kids;
	}

	//Wraps around the MutationOperation object and spits out a mutant
	//version of this Individual (which is a new instance of Individual)
	Individual mutationOperation() {
		int mutantGenome[];
		Individual mutant;

		newGenome = myMutation.mutate(genome);
		mutant = new Individual(myGenePools, myCrossover, myMutation, myFunction, mutantGenome);
	}

	int checkFitness() {
		int myFitness;

		myFitness = myFunction.checkFitness(myGenePools, genome);

		return myFitness;
	}

	//For populating HierarchicalGenePools - basically, use this Individual
	//as a template, just generate a new genome for it
	Individual makeRandomCopy() {
		Individual myCopy;

		myCopy = new Individual(myGenePools, myCrossover, myMutation, myFunction);

		return myCopy;
	}

	//In case we need to copy a given Individual's gene pool/function set,
	//but with a new genome
	//WARNING - THIS IS VERY DANGEROUS IF DONE MANUALLY
	//If the chromosomes in newGenome are out of range for their gene
	//pools, bad things will happen
	Individual makeSpecifiedCopy(int[] newGenome) {
		Individual myCopy;

		myCopy = new Individual(myGenePools, myCrossover, myMutation, myFunction, newGenome);

		return myCopy;
	}

	//Necessary for species verification
	GenePool[] getGenePoolList() {
		return myGenePools;
	}

	//Necessary for crossover
	int[] getGenome() {
		return genome;
	}

	//In a hierarchical GA, it's important to know whether or not two individuals
	//are from the same part of the hierarchy before attempting to breed them
	//Comparing which gene pools they draw from provides an easy way to do this
	boolean sameSpecies(Individual otherIndividual) {
		GenePool otherGuysPools = otherIndividual.getGenePoolList();
		int otherGuysLength = 0;

		//First, a rough check
		otherGuysLength = sizeof(otherGuysPools)/sizeof(GenePool);

		if (otherGuysLength != genomeLength) {
			return false;
		}

		//Now, more detailed inspection
		for (int i = 0; i < genomeLength; i++) {
			if (myGenePools[i] != otherGuysPools[i]) {
				return false;
			}
		}

		return true;
	}
}
