#include "CrossoverOperation.hpp"
#include "MutationOperation.hpp"
#include "FitnessFunction.hpp"
#include "ToStringFunction.hpp"
#include "Genome.hpp"
#include "PropertiesList.hpp"
#include <string>
#pragma once

/*
* The Individual class is exactly what the name implies - a member of the
* population of a GA. This class is meant to be completely generic - it
* relies on its various subclasses to perform genetic operations and give the
* information it contains any real "meaning".
*/

class Individual {
	private:

	protected:
	//The Individual's species ID - used for checking whether or not two
	//Individuals are of the same species for crossover
	unsigned speciesID;

	//The genome is represented as a series of integers which refer to
	//specific individuals in each gene pool - this frees the individual
	// from reliance on a specific gene type, and lets us mix hierarchical
	//and non-hierarchical genes freely by varying which gene pools it
	// draws from
	Genome * genome;

	//An Individual's "properties" are a series of quantitative
	//phenotypic measurements - they are determined during the fitness
	//evaluation, and are meant to be used by the higher levels of a
	//hierarchical GA
	PropertiesList * properties;

	CrossoverOperation * myCrossover;
	MutationOperation * myMutation;
	FitnessFunction * myFunction;
	ToStringFunction * myToString;

	//This allows us to do some interesting things with fitness propagation
	//without causing problems with the fitness function
	bool fitnessOverridden;

	//For TRUE deep copying - this way, we can create an Individual with
	//a fully specified everything
	Individual(
		Genome * newGenome,
		CrossoverOperation * newCrossover,
		MutationOperation * newMutation,
		FitnessFunction * newFitness,
		unsigned newSpeciesID,
		PropertiesList * newProperties,
		ToStringFunction * newToString,
		bool artificiality
	);

	public:
	//Basic constructor - lets us have a completely generic Individual
	//that doesn't know what the heck is going on inside it
	Individual(
		GeneNode ** newGeneNodes,
		int newGenomeLength,
		CrossoverOperation * newCrossover,
		MutationOperation * newMutation,
		FitnessFunction * newFitness,
		ToStringFunction * newToString
	);

	//Lets us create an otherwise random Individual with a specified
	//species ID
	Individual(
		GeneNode ** newGeneNodes,
		int newGenomeLength,
		CrossoverOperation * newCrossover,
		MutationOperation * newMutation,
		FitnessFunction * newFitness,
		ToStringFunction * newToString,
		unsigned newSpeciesID
	);

	//Constructor that lets us create an Individual with a fully specified
	//genome - necessary for crossover/mutation
	Individual(
		Genome * newGenome,
		CrossoverOperation * newCrossover,
		MutationOperation * newMutation,
		FitnessFunction * newFitness,
		ToStringFunction * newToString,
		unsigned newSpeciesID
	);

	~Individual();

	void init(
		GeneNode ** newGeneNodes,
		int newGenomeLength,
		CrossoverOperation * newCrossover,
		MutationOperation * newMutation,
		FitnessFunction * newFitness,
		ToStringFunction * newToString,
		unsigned newSpeciesID
	);

	//Exactly what it says on the tin - wraps around the CrossoverOperation
	//and spits out two offspring (which are new instances of Individual)
	//Returns NULL if the two parents have different gene pools
	Individual ** crossoverOperation(Individual * otherParent);

	//Wraps around the MutationOperation object and spits out a mutant
	//version of this Individual (which is a new instance of Individual)
	Individual * mutationOperation();

	int checkFitness();

	PropertiesList * getProperties();
	int getFitness();

	unsigned getSpeciesID();

	Individual * deepCopy();
	Individual * copyWithNewGenome(Genome * newGenome);

	//For populating PopulationNodes - basically, use this Individual
	//as a template, just generate a new genome for it
	Individual * makeRandomCopy();

	//In case we need to copy a given Individual's gene pool/function set,
	//but with a new genome
	//WARNING - THIS IS VERY DANGEROUS IF DONE MANUALLY
	//If the chromosomes in newGenome are out of range for their gene
	//pools, bad things will happen
	Individual * makeSpecifiedCopy(int newGenome[]);

	//Necessary for species verification
	GeneNode ** getGeneNodeList();

	//Necessary for crossover
	Genome * getGenome();

	void runHierarchicalGenerations();

	void setFitness(int newFitness);
	void setArtificiality(bool newArtificiality);

	//In a hierarchical GA, it's important to know whether or not two
	//individuals are from the same part of the hierarchy before attempting
	//to breed them
	//Comparing which gene pools they draw from provides an easy way to do
	//this
	bool sameSpecies(Individual * otherIndividual);

	int getGenomeLength();
	bool usesComponent(Individual * component);

	std::string toGenomeString();
	std::string toString();
};
