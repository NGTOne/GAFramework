#include "CrossoverOperation.h"
#include "MutationOperation.h"
#include "FitnessFunction.h"
#include <string>
#pragma once

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
	GenePool ** myGenePools;

	CrossoverOperation * myCrossover;
	MutationOperation * myMutation;
	FitnessFunction * myFunction;

	public:
	//Doesn't actually do anything - DO NOT USE
	Individual();

	//Basic constructor - lets us have a completely generic Individual
	//that doesn't know what the heck is going on inside it
	Individual(GenePool ** newGenePools, int newGenomeLength, CrossoverOperation * newCrossover, MutationOperation * newMutation, FitnessFunction * newFitness);

	//Constructor that lets us create an Individual with a fully specified
	//genome - necessary for crossover/mutation
	Individual(GenePool ** newGenePools, int newGenomeLength, CrossoverOperation * newCrossover, MutationOperation * newMutation, FitnessFunction * newFitness, int newGenome[]);

	void init(GenePool ** newGenePools, int newGenomeLength, CrossoverOperation * newCrossover, MutationOperation * newMutation, FitnessFunction * newFitness);

	//Exactly what it says on the tin - wraps around the CrossoverOperation
	//and spits out two offspring (which are new instances of Individual)
	//Returns NULL if the two parents have different gene pools
	Individual ** crossoverOperation(Individual * otherParent);

	//Wraps around the MutationOperation object and spits out a mutant
	//version of this Individual (which is a new instance of Individual)
	Individual * mutationOperation();

	int checkFitness();

	//For populating HierarchicalGenePools - basically, use this Individual
	//as a template, just generate a new genome for it
	Individual * makeRandomCopy();

	//In case we need to copy a given Individual's gene pool/function set,
	//but with a new genome
	//WARNING - THIS IS VERY DANGEROUS IF DONE MANUALLY
	//If the chromosomes in newGenome are out of range for their gene
	//pools, bad things will happen
	Individual * makeSpecifiedCopy(int newGenome[]);

	//Necessary for species verification
	GenePool ** getGenePoolList();

	//Necessary for crossover
	int * getGenome();

	void runHierarchicalGenerations();

	//In a hierarchical GA, it's important to know whether or not two
	//individuals are from the same part of the hierarchy before attempting
	//to breed them
	//Comparing which gene pools they draw from provides an easy way to do
	//this
	bool sameSpecies(Individual * otherIndividual);

	int getGenomeLength();

	std::string toString();
};
