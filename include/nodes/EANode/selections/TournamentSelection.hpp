#ifndef NODES_EANODE_SELECTIONS_TournamentSelection
#define NODES_EANODE_SELECTIONS_TournamentSelection

#include "../SelectionStrategy.hpp"
#include <string>
#include <vector>

#define DEFAULT_TOURNAMENT_SIZE 2

class TournamentSelection : public SelectionStrategy {
	private:

	protected:
	unsigned int tournamentSize;
	void sortByFitness(
		std::vector<unsigned int>& indexes,
		std::vector<Fitness>& fitnesses
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
		std::vector<Fitness> fitnesses
	);
	std::string toString();
};

#endif
