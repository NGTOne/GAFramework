//This abstract class serves as a general base for all selection strategies,
//allowing any HierarchicalGenePool to use any strategy you might want

#include <random>
#include <chrono>
using namespace std;

class SelectionStrategy {
	private:

	protected:
	unsigned seed;
	double crossoverRate;
	int numElites;

	public:

	SelectionStrategy(double newCrossoverRate, int newNumElites) : crossoverRate(newCrossoverRate), numElites(newNumElites) {
		seed = chrono::system_clock::now().time_since_epoch().count();
	}

	SelectionStrategy(unsigned newSeed, double newCrossoverRate, int newNumElites) : seed(newSeed), crossoverRate(newCrossoverRate), numElites(newNumElites) {}

	Individual[] sortPopulation(Individual initialPopulation[], int initialFitnesses[], int eliteLocations[], int populationSize) {
		//Since we're unlikely to be dealing with gigantic populations,
		//a simple sort that's O(n^2) or better and easy to implement
		//will suffice here.
		//TODO: Make it more efficient
		Individual tempIndividual;
		int temp;
		int tempBool;

		for (int i = 0; i < populationSize; i++) {
			for (int k = 0; k < populationSize; k++) {
				if (initialFitnesses[i] > initialFitnesses[k]) {
					tempIndividual = initialPopulation[i];
					temp = initialFitnesses[i];
					tempBool = eliteLocations[i];

					initialPopulation[i] = initialPopulation[k];
					initialFitnesses[i] = initialFitnesses[k];
					eliteLocations[i] = eliteLocations[k];

					initialPopulation[k] = tempIndividual;
					initialFitnesses[k] = temp;
					eliteLocations[k] = tempBool;
				}
			}
		}

		return initialPopulation;
	}

	int getParent(int populationFitnesses[], int populationSize);

	Individual[] breedMutateSelect(Individual initialPopulation[], int populationFitnesses[], int populationSize) {
		Individual mutantChildren[populationSize];
		Individual crossoverChildren[populationSize];
		Individual finalPopulation[populationSize];
		Individual overallPopulation[populationSize*3];
		int newPopulationFitnesses[populationSize*3];
		int finalPopulationFitnesses[populationSize];
		int eliteLocations[populationSize];
		int newEliteLocations[populationSize*3];

		Individual firstParent;
		Individual secondParent;
		Individual children[];

		int firstIndex;
		int secondIndex;

		for (int i = 0; i < populationSize; i++) {
			eliteLocations[i] = 0;
			finalPopulationFitnesses[i] = 0;
		}

		for (int i = 0; i < populationSize*3; i++) {
			newPopulationFitnesses[i] = 0;
			newEliteLocations[i] = 0;
		}

		//Each individual produces one mutant
		for (int = 0; i < populationSize; i++) {
			mutantChildren[i] = initialPopulation[i].mutationOperation();
		}

		//Each pair of individuals produces two children
		//We mess with the population size to prevent array size
		//overruns
		for (int i = 0; i < ((populationSize/2)*2); i+=2) {
			firstIndex = getParent(populationFitnesses, populationSize);
			secondIndex = getParent(populationFitnesses, populationSize);
			firstParent = initialPopulation[firstIndex];
        	        secondParent = initialPopulation[secondIndex];

                	children = firstParent.crossoverOperation(secondParent);

			crossoverChildren[i] = children[0];
			crossoverChildren[i+1] = children[1];
		}

		//Pick the elites - we can assume that the initial list has
		//been sorted during the last generation
		//If the number of elites is equal to or greater than the 
		//population size, we just mark the entire population as elite
		//and call it a day, though naturally this scenario is rather
		//silly
		for (int i = 0; i < numElites && i < populationSize; i++) {
			eliteLocations[i] = 1;
		}


		//OK, now we have all the results of our breeding and mutation
		//Time to pick the ones that will move on to the next
		//generation
		//First, we lump them all together into one big population
		for (int i = 0; i < populationSize; i++) {
			overallPopulation[i] = originalPopulation[i];
			newPopulationFitnesses[i] = originalFitnesses[i];
			newEliteLocations[i] = eliteLocations[i];
			overallPopulation[i+populationSize] = mutantChildren[i];
			newPopulationFitnesses[i+populationSize] = mutantChildren[i].checkFitness();
			overallPopulation[i+(populationSize*2)] = crossoverChildren[i];
			newPopulationFitnesses[i+(populationSize*2)] = crossoverChildren[i].checkFitness();
		}

		//Now, of course, we sort them
		overallPopulation = sortPopulation(overallPopulation, newPopulationFitnesses, newEliteLocations, populationSize*3);

		//Since they're sorted, the best of the new generation can
		//simply be pulled from the top of the list
		for (int i = 0; i < populationSize; i++) {
			finalPopulation[i] = overallPopulation[i];
			finalPopulationFitnesses[i] = newPopulationFitnesses[i];
		}

		//Now, we add the elites back in - some of them may have been
		//pushed out of the top spots by the newcomers (since we're
		//only returning the top spots, this is needed to ensure that
		//the elites are actually sent on to the next generation)
		for (int i = 0; i < numElites; i++) {
			if (populationFitnesses[i] > finalPopulationFitnesses[(populationSize-1)-i]) {
				finalPopulation[(populationSize-1)-i] = originalPopulation[i];
				finalPopulationFitnesses[(populationSize-1)-i] = originalFitnesses[i];
			}
		}

		//Return the new population and fitness values
		originalFitnesses = finalPopulationFitnesses;
		return finalPopulation;
	}
}
