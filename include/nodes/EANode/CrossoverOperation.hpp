#pragma once
#include "../../core/Genome.hpp"
#include <random>
#include <string>
#include <vector>

#define DEFAULT_NUM_OFFSPRING 2

/*
* This class serves as an abstract base for crossover operators, allowing
* us to create whatever crossover operators we need to.
*/

class CrossoverOperation {
	private:

	protected:
	unsigned seed;
	unsigned int numOffspring;
	std::mt19937 generator;

	void init(unsigned int numOffspring, unsigned seed);
	unsigned int maxPairings(
		unsigned int numParents,
		unsigned int pairingSize
	);
	std::vector<int> getParents(
		int numAvailableParents,
		int desiredParents,
		std::vector<std::vector<int>> & previousPairings
	);

	std::vector<std::vector<int>> getGenomes(std::vector<Genome*> parents);
	std::vector<std::vector<Locus*>> getLoci(std::vector<Genome*> parents);

	public:
	CrossoverOperation();
	CrossoverOperation(unsigned int numOffspring);
	CrossoverOperation(unsigned int numOffspring, unsigned seed);
	virtual std::vector<Genome*> crossOver(std::vector<Genome*> genomes)=0;
	virtual std::string toString()=0;
};

