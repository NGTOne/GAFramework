#ifndef INSTRUMENTS_POPULATION_GenerationHammingDistanceCSV
#define INSTRUMENTS_POPULATION_GenerationHammingDistanceCSV

#include "CSVInstrument.hpp"
#include <vector>
#include <map>

class GenerationHammingDistanceCSV: public CSVInstrument {
	private:

	protected:
	std::vector<std::string> targetString;

	unsigned int checkHammingDistance(Genome* target);
	void reportDistances();

	public:
	GenerationHammingDistanceCSV(
		PopulationNode* target,
		std::string outFile,
		std::vector<std::string> targetString
	);

	void initialReport();
	void runtimeReport();
	void endReport();
};

#endif
