#include "../nodes/EANode/SelectionStrategy.hpp"
#include <string>
#include <vector>
#pragma once

#define DEFAULT_TOURNAMENT_SIZE 2

class TournamentSelection : public SelectionStrategy {
	private:

	protected:
	unsigned int tournamentSize;
	void sortByFitness(
		std::vector<unsigned int> & indexes,
		std::vector<float> & fitnesses
	);

	void init(unsigned int tournamentSize);

	public:
	TournamentSelection(double crossoverRate);
	TournamentSelection(double crossoverRate, unsigned int tournamentSize);
	TournamentSelection(
		double crossoverRate,
		unsigned int tournamentSize,
		unsigned int seed
	);
        
	unsigned int getParent(
		std::vector<Genome*> population,
		std::vector<float> fitnesses
	);
	std::string toString();
};
