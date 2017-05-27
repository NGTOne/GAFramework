#ifndef INSTRUMENTS_POPULATION_GenerationBestFitnessCSV
#define INSTRUMENTS_POPULATION_GenerationBestFitnessCSV

#include "GenerationalCSVInstrument.hpp"
#include <vector>
#include <map>

class GenerationBestFitnessCSV: public GenerationalCSVInstrument {
	private:

	protected:
	std::vector<double> fitnesses;
	void report();

	public:
	GenerationBestFitnessCSV(
		PopulationNode* target,
		std::string outFile
	);

	void endReport();
};

#endif
