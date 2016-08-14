#ifndef INSTRUMENTS_POPULATION_GenerationHammingDistanceCSV
#define INSTRUMENTS_POPULATION_GenerationHammingDistanceCSV

#include "GenerationalCSVInstrument.hpp"
#include <vector>
#include <map>

class GenerationHammingDistanceCSV: public GenerationalCSVInstrument {
	private:

	protected:
	std::vector<std::string> targetString;

	unsigned int checkHammingDistance(Genome* target);
	void report();

	public:
	GenerationHammingDistanceCSV(
		PopulationNode* target,
		std::string outFile,
		std::vector<std::string> targetString
	);
};

#endif
