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
		std::vector<int> indexes,
		std::vector<int> fitnesses
	);

	void init(unsigned int tournamentSize);

	public:
	TournamentSelection(double crossoverRate);
	TournamentSelection(double crossoverRate, unsigned int tournamentSize);
	TournamentSelection(
		double crossoverRate,
		unsigned int tournamentSize,
		unsigned seed
	);
        
	int getParent(std::vector<int> populationFitnesses);
	std::string toString();
};
