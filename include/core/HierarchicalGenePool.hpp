//This is a dual-purpose class for gene pools - it serves as a "base"
//GA, and also as a gene pool for individuals in hierarchical GAs
//Since these functions are, by and large, very similar, they can be
//combined together into one class
#include "GenerationModel.hpp"
#include "EndCondition.hpp"
#include <string>
#pragma once

class HierarchicalGenePool : public GenePool {
	private:

	protected:
	Individual ** myPopulation;

	int * populationFitnesses;

	int maxGenerations;
	int currentGeneration;

	bool optimumFound;

	//Specifies how many generations should pass by "silently"
	//every time nextGeneration() is called - might be a useful parameter
	//for HGAs (to accelerate growth at the lower levels)
	int numIterationsPerGeneration;

	GenerationModel * myModel;

	//Allows us to specify different "evaluation" end conditions, rather
	//than simply being bound to fitness evaluations
	EndCondition * myCondition;

	//Used to decrease unnecessary verbosity in toString()
	bool readOnce;

	public:

	void sortPopulation();

	HierarchicalGenePool(int newPopulationSize, Individual * templateIndividual, int myMaxGenerations, int numIterations, GenerationModel * newModel, EndCondition * newCondition);

        HierarchicalGenePool(int newPopulationSize, Individual * templateIndividual, int myMaxGenerations, int numIterations, int newSeed, GenerationModel * newModel, EndCondition * newCondition);

	~HierarchicalGenePool();

	void init(int newPopulationSize, Individual * templateIndividual, int myMaxGenerations, int numIterations, GenerationModel * newModel, EndCondition * newCondition);

	//Evaluates the fitnesses of the population of this particular
	//GenePool - basically a convenience thing
	void evaluateFitnesses();

	//Evaluates the fitnesses of a given population of individuals
	//Doesn't care what their genetic makeup is - uses their fitness
	//functions
	int * evaluateFitnesses(Individual ** populationToEval, int populationToEvalSize);

	int getHighestFitness();

	//When we need a specific individual
	void * getIndex(int index);

	void * getFittest();

	//Run one generation
	void nextGeneration();

	//For HGAs - if we want to run multiple generations of a lower-level
	//gene pool for every one of a higher-level one, this is how
	//Basically a loop wrapped around nextGeneration()
	void runGenerations();

	std::string toString();
};
