#include "GenerationModel.hpp"
#include "EndCondition.hpp"
#include "FitnessPropagator.hpp"
#include <string>
#pragma once

/*
* The HierarchicalGenePool class, which extends GenePool, serves two roles:
*
* First, it is capable of iterating generations and performs all of the
* functions of a basic genetic algorithm, and a single example of this class`
* (when properly initialized) can be used to create a GA.
*
* Secondly, it can be used as a gene pool for hierarchical GAs, providing
* its population of Individuals as genes for other Individuals that are
* higher up the hierarchy.
*
* These functions are very similar (especially since, in the usual conception
* of HGAs, every node in the hierarchical GA tree is essentially its own
* self-contained GA), and are therefore combined into one class rather than
* being split apart.
*/

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

	FitnessPropagator * myPropagator;

	//Allows us to specify different "evaluation" end conditions, rather
	//than simply being bound to fitness evaluations
	EndCondition * myCondition;

	//Used to decrease unnecessary verbosity in toString()
	bool readOnce;

	public:

	void sortPopulation();
	void setFitnessAtIndex(int index, int newFitness);

	int getFitnessAtIndex(int index);

	HierarchicalGenePool(int newPopulationSize, Individual * templateIndividual, int myMaxGenerations, int numIterations, GenerationModel * newModel, EndCondition * newCondition, FitnessPropagator * newPropagator);

        HierarchicalGenePool(int newPopulationSize, Individual * templateIndividual, int myMaxGenerations, int numIterations, int newSeed, GenerationModel * newModel, EndCondition * newCondition, FitnessPropagator * newPropagator);

	~HierarchicalGenePool();

	void init(int newPopulationSize, Individual * templateIndividual, int myMaxGenerations, int numIterations, GenerationModel * newModel, EndCondition * newCondition, FitnessPropagator * newPropagator);

	//Evaluates the fitnesses of the population of this particular
	//GenePool - basically a convenience thing
	void evaluateFitnesses();

	//Wraps around the fitness propagator and allows us to call it
	//recursively
	void propagateFitnesses();

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
