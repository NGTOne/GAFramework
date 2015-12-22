//This abstract class serves as a general base for all generation models,
//allowing any PopulationNode to use any model you might want

#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include "core/SelectionStrategy.hpp"
#include "core/EvolutionarySystem.hpp"

using namespace std;

EvolutionarySystem::EvolutionarySystem(SelectionStrategy * newStrategy) {
	seed = chrono::system_clock::now().time_since_epoch().count();
	init(seed, newStrategy);
}

EvolutionarySystem::EvolutionarySystem(unsigned newSeed, SelectionStrategy * newStrategy) {
	init(newSeed, newStrategy);
}

void EvolutionarySystem::init(unsigned newSeed, SelectionStrategy * newStrategy) {
	seed = newSeed;
	mt19937 newGenerator(seed);
	generator = newGenerator;
	myStrategy = newStrategy;
}

void EvolutionarySystem::sortPopulation(Individual ** initialPopulation, int * initialFitnesses, int populationSize) {
	int topIndex = populationSize-1;
	int splitIndex;
	Individual ** leftPopulation;
	Individual ** rightPopulation;
	int * leftFitnesses;
	int * rightFitnesses;

	if (populationSize > 1) {
		splitIndex = topIndex/2;
		leftPopulation = (Individual**)malloc(sizeof(Individual*)*(splitIndex+1));
		rightPopulation = (Individual**)malloc(sizeof(Individual*)*(topIndex-splitIndex));

		leftFitnesses = (int*)malloc(sizeof(int)*(splitIndex+1));
		rightFitnesses = (int*)malloc(sizeof(int)*(topIndex-splitIndex));

		for (int i = 0; i <= splitIndex; i++) {
			leftPopulation[i] = initialPopulation[i];
			leftFitnesses[i] = initialFitnesses[i];
		}

		for (int i = 0; i < topIndex-splitIndex; i++) {
			rightPopulation[i] = initialPopulation[splitIndex+i+1];
			rightFitnesses[i] = initialFitnesses[splitIndex+i+1];
		}

		sortPopulation(leftPopulation, leftFitnesses, splitIndex+1);
		sortPopulation(rightPopulation, rightFitnesses, (topIndex-splitIndex));

		int leftIndex = 0;
		int rightIndex = 0;
		int overallIndex = 0;

		while (leftIndex <= splitIndex || rightIndex < topIndex-splitIndex) {
			if (leftIndex <= splitIndex && rightIndex < topIndex-splitIndex) {
				if (leftFitnesses[leftIndex] > rightFitnesses[rightIndex]) {
					initialPopulation[overallIndex] = leftPopulation[leftIndex];
					initialFitnesses[overallIndex++] = leftFitnesses[leftIndex++];
				} else {
					initialPopulation[overallIndex] = rightPopulation[rightIndex];
					initialFitnesses[overallIndex++] = rightFitnesses[rightIndex++];
				}
			} else {
				if (leftIndex <= splitIndex) {
					initialPopulation[overallIndex] = leftPopulation[leftIndex];
					initialFitnesses[overallIndex++] = leftFitnesses[leftIndex++];
				}

				if (rightIndex < topIndex-splitIndex) {
					initialPopulation[overallIndex] = rightPopulation[rightIndex];
					initialFitnesses[overallIndex++] = rightFitnesses[rightIndex++];
				}
			}
		}

		free(leftPopulation);
		free(rightPopulation);
		free(leftFitnesses);
		free(rightFitnesses);
	}
}

int EvolutionarySystem::getParent(int * populationFitnesses, int populationSize) {
	return myStrategy->getParent(populationFitnesses, populationSize);
}

string EvolutionarySystem::toString() {
	string returnString = "";
        stringstream ss;
	
	ss << "Random seed: " << seed << "\nSelection Strategy Info:\n";

	ss << myStrategy->toString();

	returnString = ss.str();

	return returnString;
}
