#include "secondary-pop-nodes/annealer/SimulatedAnnealer.hpp"
#include <string>
#include <sstream>
#include <random>
#include <cmath>

using namespace std;

SimulatedAnnealer::SimulatedAnnealer(
	Individual * templateIndividual,
	bool maximize,
	int maxIterations,
	int accelerationFactor,
	TemperatureSchedule * schedule,
	EndCondition * condition,
	FitnessPropagator * propagator
) : PopulationNode(
	1,
	templateIndividual,
	maxIterations,
	accelerationFactor,
	NULL,
	condition,
	propagator
) {
	init(maximize, schedule);
}

SimulatedAnnealer::SimulatedAnnealer(
	int populationSize,
	Individual * templateIndividual,
	bool maximize,
	int maxIterations,
	int accelerationFactor,
	TemperatureSchedule * schedule,
	EndCondition * condition,
	FitnessPropagator * propagator
) : PopulationNode(
	populationSize,
	templateIndividual,
	maxIterations,
	accelerationFactor,
	NULL,
	condition,
	propagator
) {
	init(maximize, schedule);
}

SimulatedAnnealer::SimulatedAnnealer(
	Individual * templateIndividual,
	bool maximize,
	int maxIterations,
	int accelerationFactor,
	TemperatureSchedule * schedule,
	EndCondition * condition,
	FitnessPropagator * propagator,
	unsigned seed
) : PopulationNode(
	1,
	templateIndividual,
	maxIterations,
	accelerationFactor,
	seed,
	NULL,
	condition,
	propagator
) {
	init(maximize, schedule);
}

SimulatedAnnealer::SimulatedAnnealer(
	int populationSize,
	Individual * templateIndividual,
	bool maximize,
	int maxIterations,
	int accelerationFactor,
	TemperatureSchedule * schedule,
	EndCondition * condition,
	FitnessPropagator * propagator,
	unsigned seed
) : PopulationNode(
	populationSize,
	templateIndividual,
	maxIterations,
	accelerationFactor,
	seed,
	NULL,
	condition,
	propagator
) {
	init(maximize, schedule);
}

void SimulatedAnnealer::init(bool maximize, TemperatureSchedule * schedule) {
	this->maximize = maximize;
	this->schedule = schedule;
}

Individual ** SimulatedAnnealer::newPopulation() {
	Individual ** population = (Individual**)malloc(
		sizeof(Individual*)*populationSize
	);

	for (int i = 0; i < populationSize; i++) {
		population[i] = getNeighbour(myPopulation[i]);
	}

	return population;
}

int SimulatedAnnealer::compareNeighbourliness(
	Individual * base,
	Individual * target
) {
	string basePhenotype = base->toGenomeString();
	string targetPhenotype = target->toGenomeString();
	int length = basePhenotype.length();

	int diff = 0;
	for (int i = 0; i < length; i++) {
		diff += abs(basePhenotype[i]-targetPhenotype[i]);
	}

	return diff;
}

Individual * SimulatedAnnealer::getNeighbour(Individual * target) {
	int genomeLength = target->getGenomeLength();
	Individual ** neighbours = (Individual**)malloc(
		sizeof(Individual*)*genomeLength
	);
	Individual * temp;
	Genome * tempGenome;

	Genome * baseGenome = target->getGenome();
	GeneNode ** nodes = baseGenome->getGeneNodes();
	int * genes = baseGenome->getGenome();
	int diff;

	for (int i = 0; i < genomeLength; i++) {
		int lowestDiff = 0;
		Individual * nearestKnownNeighbour = NULL;

		// Since we don't know where our nearest neighbour is in a
		// population of components, we have to cycle through them all
		int numAlleles = nodes[i]->getPopulationSize();
		for (int k = 0; k < numAlleles; k++) {
			if (genes[i] == k) {
				if (k < numAlleles - 1) {
					k++;
				} else {
					break;
				}
			}

			int * tempGenes = (int*)malloc(
				sizeof(int)*genomeLength
			);

			for (int c = 0; c < genomeLength; c++) {
				tempGenes[c] = genes[c]; // Reset
			}

			tempGenes[i] = k;

			tempGenome = new Genome(
				tempGenes,
				genomeLength,
				nodes
			);

			temp = target->copyWithNewGenome(tempGenome);
			delete(tempGenome);
			free(tempGenes);
			diff = compareNeighbourliness(target, temp);

			if ((diff < lowestDiff && diff > 0) || lowestDiff == 0) {
				delete(nearestKnownNeighbour);
				nearestKnownNeighbour = temp;
				lowestDiff = diff;
			} else {
				delete(temp);
			}
		}

		if (lowestDiff == 0) {
			// The lowest diff being zero means that we have no
			// neighbours (i.e. all the available choices result
			// in no change)
			neighbours[i] = NULL;
		} else {
			neighbours[i] = nearestKnownNeighbour;
		}
	}

	uniform_int_distribution<int> neighbourDistribution(0, genomeLength-1);
	int choice = neighbourDistribution(generator);

	// Make sure we're not picking identical values over and over again
	for (int i = 0; i < genomeLength && neighbours[choice] == NULL; i++) {
		choice = neighbourDistribution(generator);
	}

	if (neighbours[choice] == NULL) return target;
	int targetFitness = target->checkFitness();
	int neighbourFitness = neighbours[choice]->checkFitness();

	Individual * neighbour = neighbours[choice]->deepCopy();
	for (int i = 0; i < genomeLength; i++) {
		delete(neighbours[i]);
	}

	free(neighbours);

	if (
		(maximize && targetFitness < neighbourFitness) ||
		(!maximize && targetFitness > neighbourFitness)
	) {
		return neighbour;
	} else {
		double temp = schedule->currentTemp(currentGeneration);
		if (temp == 0) {
			delete(neighbour);
			return target;
		}

		int delta = maximize ? neighbourFitness - targetFitness :
			targetFitness - neighbourFitness;

		double probability = exp(-delta/temp);

		uniform_real_distribution<double>
			goingWrongWayDistribution(0, 1);

		if (goingWrongWayDistribution(generator) < probability) {
			return neighbour;
		} else {
			delete(neighbour);
			return target;
		}
	}
}

string SimulatedAnnealer::toString() {
	stringstream ss;

	ss << "Population size: " << populationSize << "\n";
	ss << populationStrings();

	if (!readOnce) ss << "Seed: " << seed << "\n";
	readOnce = true;

	return ss.str();
}
